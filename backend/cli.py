from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path
from typing import Any

if __package__ in {None, ""} :
    sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from backend.services import AnalysisService, FetchService, create_platform

def success(payload: dict[str, Any]) -> int:
    print(json.dumps({"status": "success", **payload}, ensure_ascii=True))
    return 0

def failure(exc: Exception) -> int:
    print(json.dumps({"status" : "error", "error": str(exc)}, ensure_ascii=True), file = sys.stderr)
    return 1

def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="CPSE Python bcakend")
    parser.add_argument("--cache-dir", type=Path, default=None, help="override cache directory")
    parser.add_argument("--platform", default="codeforces", help="competitive programming platform")
    parser.add_argument("--pretty", action="store_true", help="pretty-print JSON output")

    subparser = parser.add_subparsers(dest="command", required=True)

    fetch = subparser.add_parser("fetch", help="fetch solved cf problem")
    fetch.add_argument("handle", help="cf handle")
    fetch.add_argument("--refresh-problemset", action="store_true")
    fetch.add_argument("--cache-dir", type=Path, default=argparse.SUPPRESS, help=argparse.SUPPRESS)
    fetch.add_argument("--platform", default=argparse.SUPPRESS, help=argparse.SUPPRESS)
    fetch.add_argument("--pretty", action="store_true", default=argparse.SUPPRESS, help=argparse.SUPPRESS)

    analyze = subparser.add_parser("analyze", help="analyze cf problem")
    analyze.add_argument("problem_id", help="problem id, for example 4A")
    analyze.add_argument("--cache-dir", type=Path, default=argparse.SUPPRESS, help=argparse.SUPPRESS)
    analyze.add_argument("--platform", default=argparse.SUPPRESS, help=argparse.SUPPRESS)
    analyze.add_argument("--pretty", action="store_true", default=argparse.SUPPRESS, help=argparse.SUPPRESS)

    return parser

def main (argv: list[str] | None = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)

    try :
        if args.command == "fetch":
            platform = create_platform(args.platform, cache_dir=args.cache_dir)
            problems = FetchService(platform).fetch_solved_problems(
                args.handle,
                refresh_problemset=args.refresh_problemset,
            )
            payload = {"problems": problems}
        elif args.command == "analyze":
            platform = create_platform(args.platform, cache_dir=args.cache_dir)
            payload = {"analysis": AnalysisService(platform).analyze_problem(args.problem_id)}
        else:
            parser.error("unkown command")
            return 2

        output = {"status": "success", **payload}
        print(json.dumps(output, ensure_ascii=True, indent=2 if args.pretty else None))
        return 0
    except Exception as exc:
        return failure(exc)
    
if __name__ == "__main__":
    raise SystemExit(main())