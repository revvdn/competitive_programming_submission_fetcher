from __future__ import annotations
from collections import Counter
from pathlib import Path
from typing import Any
from backend.fetcher.codeforces import get_problem_index

def normalize_problem_id(problem_id: str) -> str:
    return problem_id.strip().upper()

def analyze_problem (problem_id:str, cache_dir: Path | None = None) -> dict[str, Any]:
    normalize = normalize_problem_id(problem_id)
    problems = get_problem_index(cache_dir = cache_dir)

    if normalize not in problems:
        raise ValueError(f"problem not found")
    
    problem = problems[normalize]
    rating = problem.get("rating")
    tags = problem.get("tags", [])

    similar: list[dict[str, Any]] = []
    for pid, candidate in problems.items():
        if pid == normalize :
            continue

        same_rating = rating is not None and candidate.get("rating") == rating
        shared_tags = sorted(set(tags).intersection(candidate.get("tags", [])))

        if same_rating and shared_tags :
            similar.append({
                "problemId": pid,
                "contestId": candidate["contestId"],
                "index": candidate["index"],
                "name": candidate["name"],
                "rating": candidate["rating"],
                "tags": candidate["tags"],
                "shared_tags": shared_tags,
            })
    
    similar.sort(key=lambda item: (-len(item["shared_tags"]), item["problemId"]))

    nearby = [
        item 
        for item in problems.values() 
        if item.get("rating") is not None and rating is not None and abs(item["rating"] - rating) <= 200
    ]

    distribution = Counter(str(item["rating"]) for item in nearby)

    return {
        "problemID": normalize,
        "name": problem["name"],
        "rating": rating,
        "tags": tags,
        "similar_problems": similar[:10],
        "statistic": {
            "nearby_rating_windows": 200,
            "difficulty_distribution": dict(sorted(distribution.items(), key=lambda pair: int(pair[0]))),
            "same_rating_count": distribution.get(str(rating), 0) if rating is not None else 0,
        },
    }
        