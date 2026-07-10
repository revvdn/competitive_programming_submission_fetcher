from __future__ import annotations
from collections import Counter
from typing import Any
from backend.core import Problem
from backend.platforms import Platform

class AnalysisService:
    def __init__(self, platform: Platform) -> None:
        self.platform = platform

    def analyze_problem(self, problem_id: str) -> dict[str, Any]:
        normalized = self.normalize_problem_id(problem_id)
        problems = self.platform.fetch_problemset()
        problem = problems.get(normalized)
        
        if problem is None : 
            raise ValueError("problem not found")
        
        similar = self.similar_problems(problem, problems)
        nearby = [
            candidate for candidate in problems.values() 
            if self.is_nearby_rating(problem, candidate)
        ]
        distribution = Counter(str(item.rating) for item in nearby if item.rating is not None)

        response : dict[str, Any] = {
            **problem.to_dict(),
            "similar_problems" : similar[:10],
            "statistic": {
                "nearby_rating_windows": 200,
                "difficulty_distribution": dict(
                    sorted(distribution.items(), key=lambda pair: int(pair[0]))

                ),
                "same_rating_count": distribution.get(str(problem.rating), 0)
                if problem.rating is not None
                else 0,
            }
        }

        if self.platform.name == "atcoder":
            rating = problem.rating if problem.rating is not None else 0
            solve_time_mins = max(1, rating // 40)
            if rating >= 3000:
                solve_prob = "<1%"
            elif rating <= 0:
                solve_prob = "100%"
            else:
                prob_val = max(1, 100 - (rating // 30))
                prob_val = round(prob_val, -2)
                solve_prob = f"{prob_val}%"
            
            response["atcoder_metrics"] = {
                "solve_prob": solve_prob,
                "solve_time_mins": f"{solve_time_mins} mins",
            }
        
        return response

    def normalize_problem_id(self, problem_id: str) -> str:
        return problem_id.strip().upper()
    
    @staticmethod
    def is_nearby_rating(problem: Problem, candidate: Problem) -> bool:
        return (
            problem.rating is not None
            and candidate.rating is not None
            and abs(candidate.rating - problem.rating) <= 200
        )
    
    def similar_problems(self, problem: Problem, problems: dict[str, Problem]) -> list[dict[str, Any]]:
        similar: list[dict[str, Any]] = []
        source_tags = set(problem.tags)
        for candidate in problems.values():
            if candidate.problem_id == problem.problem_id:
                continue

            shared_tags = sorted(source_tags.intersection(candidate.tags))
            if problem.rating == candidate.rating and (shared_tags or self.platform.name == "atcoder"):
                similar.append(
                    {
                        **candidate.to_dict(),
                        "shared_tags": shared_tags,
                    }
                )

        similar.sort(key=lambda item: (-len(item["shared_tags"]), item["problemId"]))
        return similar