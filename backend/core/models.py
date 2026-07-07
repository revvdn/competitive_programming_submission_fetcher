from __future__ import annotations
from dataclasses import dataclass, field
from typing import Any

@dataclass(frozen=True)
class Problem:
    problem_id: str
    contest_id: int
    index: str
    name: str
    rating: int | None = None
    tags : tuple[str, ...] = field(default_factory=tuple)

    @classmethod
    def from_codeforces(cls, payload: dict[str, Any]) -> "Problem | None":
        if "contestId" not in payload or "index" not in payload:
            return None
        
        contest_id = int(payload["contestId"])
        index = str(payload["index"])
        return cls(
            problem_id = f"{contest_id}{index}",
            contest_id = contest_id,
            index = index,
            name = str(payload.get("name", "")),
            rating = payload.get("rating"),
            tags = tuple(str(tag) for tag in payload.get("tags", [])),
        )
    
    def to_dict(self) -> dict[str, Any]:
        return {
            "problemId": self.problem_id,
            "contestId": self.contest_id,
            "index": self.index,
            "name": self.name,
            "rating": self.rating,
            "tags": list(self.tags),
        }
    
@dataclass(frozen=True)
class Submission:
    submission_id: int
    problem_id: str
    contest_id: int
    index: str
    verdict: str | None
    creation_time_seconds: int

    @classmethod
    def from_codeforces(cls, payload: dict[str, Any]) -> "Submission | None":
        problem = payload.get("problem", {})
        if "contestId" not in problem or "index" not in problem:
            return None
        
        contest_id = int(problem["contestId"])
        index = str(problem["index"])
        return cls(
            submission_id = int(payload.get("id", 0)),
            problem_id = f"{contest_id}{index}",
            contest_id = contest_id,
            index = index,
            verdict = payload.get("verdict"),
            creation_time_seconds = int(payload.get("creationTimeSeconds", 0)),
        )
    
    def to_solved_problem_dict(self, problem: Problem) -> dict[str, Any]:
        return {
            **problem.to_dict(),
            "submissionId": self.submission_id,
            "solvedAt": self.creation_time_seconds,
        }
    
@dataclass(frozen=True)
class UserProfile:
    handle: str
    platform: str

@dataclass(frozen=True)
class Statistic:
    values: dict[str, Any]

@dataclass(frozen=True)
class Recommendation:
    problem: Problem
    reason: str
    score: float