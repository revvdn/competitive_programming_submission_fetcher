from __future__ import annotations

from abc import ABC, abstractmethod

from backend.core import Problem, Submission, UserProfile

class Platform(ABC):
    name: str

    @abstractmethod
    def fetch_profile(self, handle: str) -> UserProfile:
        raise NotImplementedError
    
    @abstractmethod
    def fetch_submission(self, handle: str) -> list[Submission]:
        raise NotImplementedError
    
    @abstractmethod
    def fetch_problemset(self, refresh: bool = False) -> dict[str, Problem]:
        raise NotImplementedError
    
    def fetch_problem(self, problem_id: str, refresh: bool = False) -> Problem | None: 
        return self.fetch_problemset(refresh=refresh).get(problem_id.strip().upper())
    
    def fetch_contests(self) -> list[dict]:
        return []