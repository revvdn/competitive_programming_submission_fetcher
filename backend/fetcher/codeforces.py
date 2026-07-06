from pathlib import Path
from typing import Any
from backend.services import FetchService, create_platform

PROBLEM_CACHE = "problem_cache.json"
FETCHED_FILE = "fetch_problem.json"

def cache_path(cache_dir: Path | None, name:str) -> Path:
    base = Path.cwd() / "storage" if cache_dir is None else cache_dir
    return base / name

def load_cached_json(cache_dir: Path | None, name: str) -> Any:
    path = cache_path(cache_dir, name)
    if path.exists():
        from backend.cache.manager import read_json

        return read_json(path)
    return None

def save_fetched_json(cache_dir: Path | None, name: str, data: Any) -> None:
    from backend.cache.manager import write_json

    write_json(cache_path(cache_dir, name), data)

'''
def fetch_json(url: str, params: Optional[Dict[str, Any]] = None) -> Dict[str, Any]:
    resp = session.get(url, params=params, timeout=20)
    resp.raise_for_status()
    return resp.json()
'''

def get_problem_index(cache_dir: Path | None = None, refresh: bool = False) -> dict[str, dict[str, Any]]:
    platform = create_platform("codeforces", cache_dir = cache_dir)
    problems = platform.fetch_problemset(refresh = refresh)
    
    return {problem_id: problem.to_dict() for problem_id, problem in problems.items()}
    
def load_fetch_problem(cache_dir: Path | None) -> set[str]:
    path = cache_path(cache_dir, FETCHED_FILE)
    if path.exists():
        from backend.cache.manager import read_json

        return set(read_json(path, default=[]))

    return set()

def save_fetch_problem(cache_dir: Path | None, fetch_pid: set[str]) -> None:
    from backend.cache.manager import write_json

    path = cache_path(cache_dir, FETCHED_FILE)
    write_json(path, sorted(fetch_pid))

'''
def fetch_solved_problem(handle: str, cache_dir: Optional[Path] = None, refresh_problemset: bool = False) -> List[Dict[str, Any]]:
    problems = get_problem_index(cache_dir=cache_dir, refresh=refresh_problemset)

    data = fetch_json(API_USER_STATUS, {"handle": handle})
    if data.get("status") != "OK" :
        raise RuntimeError("failed to fetch user status")
    
    submission = data.get("result", [])

    logging.info(f"fetch {len(submission)} total")

    fetch_pid = load_fetch_problem(cache_dir)

    accepted : Dict[str, Dict[str, Any]] = {}

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

        if pid not in accepted or sub.get("creationTimeSeconds", 0) > accepted[pid]["solvedAt"]:
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
'''

def fetched_solved_problems(
        handle: str, 
        cache_dir: Path | None = None,
        refresh_problemset: bool = False,
) -> list[dict[str, Any]]:
    platform = create_platform("codeforces", cache_dir = cache_dir)
    return FetchService(platform).fetch_solved_problems(
        handle,
        refresh_problemset = refresh_problemset,
    )
