import logging 
import requests
import os 
import json
from pathlib import Path
from typing import Any, Dict, List, Optional

API_USER_STATUS = "https://codeforces.com/api/user.status"
API_PROBLEMSET = "https://codeforces.com/api/problemset.problems"

CACHE_DIR = "storage"
PROBLEM_CACHE = "problem_cache.json"
FETCHED_FILE = "fetch_problem.json"

session = requests.Session()

def cache_path(cache_dir: Optional[Path], name: str) -> Path:
    base = Path.cwd() if cache_dir is None else cache_dir
    return base / name

def load_cached_json (cache_dir: Optional[Path], name: str):
    path = cache_path(cache_dir, name)
    
    if Path.exist():
        with open(path, "r", encoding="utf-8") as f:
            return json.load(f)
    return None

def save_cached_json(cache_dir: Optional[Path], name: str, data: Any) :
    base = Path.cwd() if cache_dir is None else cache_dir
    base.mkdir(parents=True, exist_ok=True)
    path = base / name
    with open(path, "w", encoding="utf-8") as f:
        json.dump(data, f)

def fetch_json(url: str, params: Optional[Dict[str, Any]] = None) -> Dict[str, Any]:
    resp = session.get(url, params=params, timeout=20)
    resp.raise_for_status()
    return resp.json()

def get_problem_index(cache_dir: Optional[Path] = None, refresh: bool = False) -> Dict[str, Dict[str, Any]]:
    if not refresh:
        cached = load_cached_json(cache_dir, PROBLEM_CACHE)
        if cached:
            data = cached
        else :
            data = fetch_json(API_PROBLEMSET)
            if data.get("status") != "OK" :
                raise RuntimeError("failed to fetch")
            save_cached_json(cache_dir, PROBLEM_CACHE, data)

        indexed: Dict[str, Dict[str, Any]] = {}
        for detail in data.get("result", {}).get("problems", []):
            if "contestId" in detail and "index" in detail:
                pid = f"{detail['contestId']}{detail['index']}"
                indexed[pid] = {
                    "problemId": pid,
                    "contestId": detail["contestId"],
                    "index": detail["index"],
                    "name": detail.get("name", ""),
                    "rating": detail.get("rating"),
                    "tags": detail.get("tags", []),
                }
        
        return indexed
    
def load_fetch_problem(cache_dir: Optional[Path]):
    path = cache_path(cache_dir, FETCHED_FILE)
    if path.exists():
        with open(path, "r", encoding="utf-8") as f:
            return set(json.load(f))
    return set()

def save_fetch_problem(cache_dir: Optional[Path], fetch_pid):
    path = cache_path(cache_dir, FETCHED_FILE)
    path.parent.mkdir(parents=True, exist_ok=True)
    with open (path, "w", encoding="utf-8") as f:
        json.dump(list(fetch_pid), f)

def fetch_solved_problem(handle: str, cache_dir: Optional[Path] = None, refresh_problemset: bool = False) -> List[Dict[str, Any]]:
    problems = get_problem_index(cache_dir=cache_dir, resfresh=refresh_problemset)

    data = fetch_json(API_USER_STATUS, {"handle": handle})
    if data.get("status") != "OK" :
        raise RuntimeError("failed to fetch user status")
    
    submission = data.get("result", [])

    logging.info(f"fetch {len(submission)} total")

    fetch_pid = load_fetch_problem(cache_dir)

    accepted = Dict[str, Dict[str, Any]] = {}

    for sub in submission:
        if sub.get("verdict") != "OK":
            continue
        problem = sub.get("problem", {})
        if "contestId" not in problem or "index" not in problem:
            continue

        pid = f"{problem['contestId']}{problem['index']}"

        if pid not in problems:
            continue
        metadata = problems[pid]
        if metadata.get("rating") is None :
            continue

        if pid not in accepted or sub.get("creationTimeSecond", 0) > accepted[pid]["solvedAt"]:
            accepted[pid] = {
                **metadata,
                "submissionId": sub.get("id"),
                "solvedAt": sub.get("creationTimeSeconds", 0),
            }
    
    result = sorted(
        accepted.values(),
        key=lambda item: (item.get("rating"), -item.get("solvedAt", 0), item.get("problemId")),
    )

    return result

