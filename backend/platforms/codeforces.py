from __future__ import annotations

from pathlib import Path
from typing import Any
from urllib.parse import urlencode
from urllib.request import urlopen
import json

try:
    import requests
except ModuleNotFoundError:
    requests = None

from backend.core import Problem, Submission, UserProfile
from backend.platforms.base import Platfrom
from backend.storage import JsonCache

API_USER_INFO = "https://codeforces.com/api/user.info"
API_USER_STATUS = "https://codeforces.com/api/user.status"
API_PROBLEMSET = "https://codeforces.com/api/problemset.problems"
PROBLEM_CACHE = "problem_cache.json"

class CodeforcesPlatform(Platfrom):
    name = "codeforces"

    def __init__(
            self, 
            cache_dir: Path | None = None,
            session: Any | None = None,
        ) -> None:
            self.cache = JsonCache(cache_dir)
            self.session = self.session or (requests.Session() if requests is not None else None)

    def fetch_profile(self, handle:str) -> UserProfile:
        data = self.fetch_json(API_USER_INFO, {"handles": handle})
        if data.get("status") != "OK":
            raise RuntimeError("failed to fetch cf profile")
        return UserProfile(handle = handle, platform=self.name)
    
    def fetch_submissions(self, handle: str) -> list[Submission]:
        data = self.fetch_json(API_USER_STATUS, {"handles": handle})
        if data.get("status") != "OK":
            raise RuntimeError("failed to fetch cf submission")
        
        submissions: list[Submission] = []
        for item in data.get("result", []):
            submission = Submission.from_codeforces(item)
            if submission is not None:
                submissions.append(submission)
        return submissions
    
    def fetch_problemset(self, refresh: bool = False) -> dict[str, Problem]:
        data = None if refresh else self.cache.read(PROBLEM_CACHE)
        if not data or "result" not in data:
            data = self.fetch_json(API_PROBLEMSET)
            if data.get("status") != "OK":
                raise RuntimeError("failed to fetch codeforces problemset")
            self.cache.write(PROBLEM_CACHE, data)

        problems: dict[str, Problem] = {}
        for item in data.get("result", {}).get("problems", []):
            problem = Problem.from_codeforces(item)
            if problem is not None:
                problems[problem.problem_id] = problem
        return problems
    
    def fetch_json(self, url: str, params: dict[str, Any] | None = None) -> dict[str, Any]:
        if self.session is None:
            query = f"?{urlencode(params)}" if params else ""
            with urlopen(f"{url}{query}", timeout=20) as response:
                return json.loads(response.read().decode("utf-8"))
            
            response = self.session.get(url, params = params, timeout =20)
            response.raise_for_status()
            return response.json()