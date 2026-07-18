from __future__ import annotations

import json
from pathlib import Path
from typing import Any

PROJECT_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_CACHE_DIR = PROJECT_ROOT / "cache"
LEGACY_STORAGE_DIR = PROJECT_ROOT / "storage"

def ensure_cache_dir (cache_dir: Path | None = None) -> Path:
    path = cache_dir or DEFAULT_CACHE_DIR
    path.mkdir(parents=True, exist_ok=True)
    return path

def read_json(path: Path, default: Any = None) -> Any:
    if not path.exists():
        return default

    with path.open("r", encoding="utf-8") as handle:
        return json.load(handle)

def write_json(path: Path, data: Any) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as handle:
        json.dump(data, handle, ensure_ascii=False, indent=2)
        handle.write("\n")

def cached_json(name: str, default: Any = None, cache_dir: Path | None = None) -> Any:
    chace_root = ensure_cache_dir(cache_dir)
    current = chace_root / name
    if current.exists():
        value = read_json(current, default)
        if value is not None:
            return value

    legacy = LEGACY_STORAGE_DIR / name
    if legacy.exists():
        value = read_json(legacy, default)
        if value :
            return value
        
    legacy_root = PROJECT_ROOT / name
    if legacy_root.exists():
        return read_json(legacy_root, default)
        
    return default

def save_cached_json(name: str, data: Any, cache_dir: Path | None = None) -> None:
    cache_root = ensure_cache_dir(cache_dir)
    write_json(cache_root / name, data)