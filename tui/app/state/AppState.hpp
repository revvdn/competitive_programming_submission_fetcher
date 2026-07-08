#pragma once
#include<string>
#include<vector>

enum class ScreenState {
    FetchForm,
    Loading,
    ProblemList,
    ProblemAnalysis,
};

struct Problem
{
    std::string contest_id;
    std::string index;
    std::string problem_id;
    std::string name;
    int rating = 0;
    std::vector<std::string> tags;
    long long solved_at = 0;
    long long submission_id = 0;
};

struct Analysis
{
    std::string problem_id;
    std::string name;
    int rating = 0;
    std::vector<std::string> tags;
    std::vector<Problem> similar_problems;
    std::vector<std::pair<std::string, int>> difficulty_distribution;
    int same_rating_count = 0;
    std::string solve_prob;
    std::string solve_time;
};

struct AppState
{
    std::string platform = "codeforces";
    std::string handle = "";
    bool loading = false;
    std::string status = "ready";
    std::string error;

    std::vector<Problem> problems;
    int selected_problem = 0;
    Analysis analysis;
    ScreenState current_screen = ScreenState::FetchForm;
};


