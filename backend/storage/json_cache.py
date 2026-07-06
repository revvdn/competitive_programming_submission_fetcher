from __future__ import annotations
from pathlib import Path
from typing import Any
from backend.cache.manager import cached_json, save_cached_json

class JsonCache:
    def __init__(self, cache_dir: Path | None = None) -> None:
        self.cache_dir = cache_dir

    def read(self, name: str, default: Any = None) -> Any:
        return cached_json(name, default=default, cache_dir=self.cache_dir)
    
    def write(self, name: str, data: Any) -> None:
        save_cached_json(name, data, cache_dir=self.cache_dir)