from __future__ import annotations
import time
from pathlib import Path
from typing import Any, List
import requests
from backend.core import Problem, Submission, UserProfile
from backend.platforms.base import Platform
from backend.storage import JsonCache

#API endpoints from Kenkoooo (repo : https://github.com/kenkoooo/AtCoderProblems.git), btw thanks a lot for providing this im very helpful with that :)
API_SUBMISSIONS = "https://kenkoooo.com/atcoder/atcoder-api/v3/user/submissions"
API_PROBLEMS = "https://kenkoooo.com/atcoder/resources/problems.json"
API_DIFFICULTIES = "https://kenkoooo.com/atcoder/resources/problem-models.json"

class AtCoderPlatform(Platform):
    name = "atcoder"

    def __init__(self, cache_dir: Path | None = None, session: Any | None = None) -> None:
        self.cache = JsonCache(cache_dir)
        self.session = session or (requests.Session() if "requests" in globals() else None)

    def fetch_profile(self, handle: str) -> UserProfile:
        return UserProfile(handle=handle, platform = self.name)
    
    def fetch_submissions(self, handle: str) -> list[Submission]:
        submission: List[Submission] = []
        from_second = 0

        while True:
            time.sleep(1)

            url = f"{API_SUBMISSIONS}?user={handle}&from_second={from_second}"
            if self.session is None:
                raise RuntimeError("request session not avaible for Atcoder")
            resp = self.session.get(url, timeout=20)
            resp.raise_for_status()
            data = resp.json()

            if not data:
                break

            for item in data:
                verdict = "OK" if item.get("result") == "AC" else item.get("result")
                problem_id = item["problem_id"]
                contest_id = str(item.get("contest_id", ""))
                index = problem_id.split("_")[-1] if "_" in problem_id else ""

                sub = Submission(
                    submission_id=int(item.get("id", 0)),
                    problem_id=problem_id,
                    contest_id=contest_id,
                    index=index,
                    verdict=verdict,
                    creation_time_seconds=int(item.get("epoch_second", 0)),
                )
                submission.append(sub)

            from_second = data[-1].get("epoch_second", from_second) + 1
            if len(data) < 500:
                break
        
        return submission
    
    def fetch_problemset(self, refresh: bool = False) -> dict[str, Problem]:
        problem_raw = None if refresh else self.cache.read("atcoder_problems.json")
        if not problem_raw:
            if self.session is None:
                raise RuntimeError("request session not avaible for AtCoderPlatform")
            resp = self.session.get(API_PROBLEMS, timeout=20)
            resp.raise_for_status()
            problem_raw = resp.json()
            self.cache.write("atcoder_problems.json", problem_raw)

        diff_raw = None if refresh else self.cache.read("atcoder_difficulties.json")
        if not diff_raw:
            if self.session is None:
                raise RuntimeError("request session not avaible")
            resp = self.session.get(API_DIFFICULTIES, timeout=20)
            resp.raise_for_status()
            diff_raw = resp.json()
            self.cache.write("atcoder_difficulties.json", diff_raw)

        rating_map: dict[str, int | None] = {}
        for pid, model in diff_raw.items():
            if isinstance(model, dict):
                rating = model.get("difficulty")
                if rating is not None :
                    rounded = int(round(float(rating) / 100.0)) * 100
                    rating_map[pid] = max(100, rounded)
                else:
                    rating_map[pid] = None
            
        problems: dict[str, Problem] = {}
        for prob in problem_raw:
            pid = prob.get("id")
            contest_id = str(prob.get("contest_id", ""))
            index = prob.get("problem_index", "") or prob.get("title", "")
            problem = Problem(
                problem_id=pid,
                contest_id=contest_id,
                index=index,
                name=prob.get("title", ""),
                rating=rating_map.get(pid),
                tags=tuple(prob.get("tags", [])),
            )
            problems[pid] = problem
        return problems
    
    def download_source(self, submission_id: int) -> str | None:
        try:
            from .atcoder_code import fetch_source_via_selenium
        except Exception:
            return None
        return fetch_source_via_selenium(submission_id, session = self.session)
    
        