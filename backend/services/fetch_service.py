from __future__ import annotations
from backend.core import Problem, Submission
from backend.platforms import Platform

class FetchService:
    def __init__(self, platform: Platform) -> None:
        self.platform = platform

    def fetch_solved_problems(self, handle: str, refresh_problemset: bool  = False) -> list[dict]:
        problems = self.platform.fetch_problemset(refresh = refresh_problemset)
        submissions = self.platform.fetch_submissions(handle)

        accepted : dict[str, Submission] = {}
        for submission in submissions:
            if submission.verdict != "OK":
                continue

            problem = problems.get(submission.problem_id)
            if problem is None or problem.rating is None:
                continue

            previous = accepted.get(submission.problem_id)
            if previous is None or submission.creation_time_seconds > previous.creation_time_seconds:
                accepted[submission.problem_id] = submission

        solved = [
            submission.to_solved_problem_dict(problems[problem_id])
            for problem_id, submission in accepted.items()
        ]
        solved.sort(key=self.solved_sort_key)
        return solved
    
    @staticmethod
    def solved_sort_keys(item: dict) -> tuple[int, int, str]:
        rating = item.get("rating")
        return (
            int(rating) if rating is not None else 10**9,
            -int(item.get("solvedAt", 0)),
            str(item.get("problemId", "")),
        )