from __future__ import annotations
from pathlib import Path
from backend.platforms import Platform

def create_platform(name: str = "codeforces", cache_dir: Path | None = None) -> Platform:
    normalized = name.strip().lower()
    if normalized in {"codeforces", "cf"}:
        from backend.platforms.codeforces import CodeforcesPlatform

        return CodeforcesPlatform(cache_dir=cache_dir)
    elif normalized in {"atcoder", "ac"}:
        from backend.platforms.atcoder import AtCoderPlatform

        return AtCoderPlatform(cache_dir=cache_dir)
    raise ValueError(f"unsupported platform: {name}")