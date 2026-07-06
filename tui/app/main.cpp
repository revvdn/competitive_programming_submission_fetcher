#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<memory>
#include<sstream>
#include<stdexcept>
#include<string>
#include<vector>

#include<ftxui/component/component.hpp>
#include<ftxui/component/event.hpp>
#include<ftxui/component/screen_interactive.hpp>
#include<ftxui/dom/elements.hpp>
#include<nlohmann/json.hpp>
#include "state/AppState.hpp"

//sigmas people dont use namespace std (actually im afraid if i naming the variable same with some of the STL, XD)
using json = nlohmann::json;

#ifndef CPSE_PROJECT_ROOT
#define CPSE_PROJECT_ROOT "."
#endif

std::string quote (const std::string& value) {
    #ifdef _WIN32
        std::string escaped = "\"";
        
        for (char c : value) {
            if (c == '"')
                escaped += "\\\"";
            else 
                escaped += c;
        }
        
        escaped += "\"";
        return escaped;

    #else
        std::string escaped = "'";
        
        for (char c : value) {
            if (c == '\'') 
                escaped += "'\\''";
            else 
                escaped += c;
        }
        
        escaped += "'";
        return escaped;
    #endif
}

std::string pythoncommand () {
    const char* configure = std::getenv("CPSE_PYTHON");
    
    if (configure && configure[0] != '\0') {
        return configure;
    }

    return "python";
}

std::string backendclipath () {
    return std::string(CPSE_PROJECT_ROOT) + "/cli.py";
}

std::string runcommand (const std::string& command) {
    #ifdef _WIN32
        FILE* pipe = _popen(command.c_str(), "r");
    #else 
        FILE* pipe = popen(command.c_str(), "r");
    #endif
        if (!pipe) 
            throw std::runtime_error("fail to start backend");

        std::string output;
        char buffer[1 << 12];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            output += buffer;
        }

    #ifdef _WIN32
        const int rc = _pclose(pipe);
    #else 
        const int rc = pclose(pipe);
    #endif
        if (rc != 0) {
            throw std::runtime_error("backend fail");
        }

        return output;
}

std::vector<std::string> tostringvector(const json& value) {
    std::vector<std::string> res;

    if (!value.is_array()) {
        return res;
    }

    for (const auto& item : value) {
        res.push_back(item.get<std::string>());
    }

    return res;
}

Problem parseproblem (const json& item) {
    Problem prob;
    prob.contest_id = item.value("contestId", 0);
    prob.index = item.value("index", "");
    prob.problem_id = item.value("problemId", std::to_string(prob.contest_id) + prob.index);
    prob.name = item.value("name", "");
    prob.rating = item.value("rating", 0);
    prob.tags = tostringvector(item.value("tags", json::array()));
    prob.solved_at = item.value("solvedAt", 0LL);
    prob.submission_id = item.value("submissionId", 0LL);
    return prob;
}

std::string join (const std::vector<std::string>& values, const std::string& separate) {
    std::ostringstream stream;

    for (size_t i = 0; i < values.size(); ++i) {
        if (i) 
            stream << separate;
        stream << values[i];
    }

    return stream.str();
}

void fetchprob (AppState& state) {
    state.loading = true;
    state.current_screen = ScreenState::Loading;
    state.error.clear();
    state.status = "fetching solved problem";

    try {
        const std::string command =
            quote(pythoncommand()) + " " + quote(backendclipath()) + " fetch " + quote(state.handle);
        const auto payload = json::parse(runcommand(command));
        
        if (payload.value("status", "") != "success") 
            throw std::runtime_error(payload.value("error", "backend error"));

        state.problems.clear();
        for (const auto& item : payload.at("problems")) {
            state.problems.push_back(parseproblem(item));
        }
        state.selected_problem = 0;
        state.status = "fetched " + std::to_string(state.problems.size()) + " solved problem";
        state.current_screen = ScreenState::ProblemList;
    } catch (const std::exception& exc) {
        state.error = exc.what();
        state.status = "fetch fail";
        state.current_screen = ScreenState::FetchForm;
    }

    state.loading = false;
}

void analyzeselected (AppState& state) {
    if (state.problems.empty())
        return;
    const Problem& selected = state.problems[state.selected_problem];
    state.error.clear();
    state.status = "analyze " + selected.problem_id + "...";

    try {
        const std::string command = 
            quote(pythoncommand()) + " " + quote(backendclipath()) + " analyze " + quote(selected.problem_id);
        const auto payload = json::parse(runcommand(command));

        if (payload.value("status", "") != "success") 
            throw std::runtime_error(payload.value("error", "unkown backend error"));

        const auto& item = payload.at("analysis");
        Analysis analysis;
        analysis.problem_id = item.value("problemId", selected.problem_id);
        analysis.name = item.value("name", selected.name);
        analysis.rating = item.value("rating", selected.rating);
        analysis.tags = tostringvector(item.value("tags", json::array()));
        analysis.same_rating_count = item.value("statistic", json::object()).value("same_rating_count", 0);

        for (const auto& similar : item.value("similar_problems", json::array())) {
            analysis.similar_problems.push_back(parseproblem(similar));
        }

        const auto distribute = item.value("statistic", json::object()).value("difficulty_distribution", json::object());
        for (auto iter = distribute.begin(); iter != distribute.end(); ++iter) {
            analysis.difficulty_distribution.push_back({iter.key(), iter.value().get<int>()});
        }

        state.analysis = analysis;
        state.status = "analysis for " + selected.problem_id;
        state.current_screen = ScreenState::ProblemAnalysis;

    } catch (const std::exception& exc) {
        state.error = exc.what();
        state.status = "analysis fail";
    }
}

ftxui::Element statusline (const AppState& state) {
    std::string message = state.error.empty() ? state.status : state.status + ": " + state.error;
    return ftxui::text(message) | (state.error.empty() ? ftxui::color(ftxui::Color::GrayDark) : ftxui::color(ftxui::Color::Red));
}

ftxui::Element helpbox() {
    return ftxui::vbox({
        ftxui::text("TAB: switch panel      ENTER: select / analyze     UP / DONW: navigate"),
        ftxui::text("ESC: back to list      Q: quit"),
    }) | ftxui::border;
}

ftxui::Element problemrow (const Problem& problem, bool select) {
    std::string pref = select ? "> " : " ";
    auto line  = ftxui::text(pref + problem.problem_id + " " + problem.name + " [" + std::to_string(problem.rating) + "]");

    if (select) 
        line = line | ftxui::inverted;

    return line;
}

ftxui::Element problemlistpane (const AppState& state) {
    std::vector<ftxui::Element> row;

    if (state.problems.empty()) 
        row.push_back(ftxui::text("no solved problem loaded yet") | ftxui::color(ftxui::Color::GrayDark));
    else {
        const int start = std::max(0, state.selected_problem - 12);
        const int end = std::min<int>(state.problems.size(), start + 24);

        for (int i = start; i < end; ++i) {
            row.push_back(problemrow(state.problems[i], i == state.selected_problem));
        }
    }

    return ftxui::vbox({
        ftxui::text("problem list") | 
        ftxui::bold,
        ftxui::separator(),
        ftxui::vbox(row) | 
        ftxui::yframe,
    }) | 
    ftxui::border | 
    ftxui::flex;
}

ftxui::Element inputpane (ftxui::Component handle_input, ftxui::Component start_button, const AppState& state) {
    return ftxui::vbox({
        ftxui::text("input") | ftxui::bold,
        ftxui::separator(),
        ftxui::text("platform"),
        ftxui::text(state.platform) | ftxui::color(ftxui::Color::Cyan),
        ftxui::text(""),
        ftxui::text("Handle"),
        handle_input -> Render(),
        ftxui::text(""),
        start_button -> Render(),
    }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 28);
}

ftxui::Element analysispane (const AppState& state) {
    std::vector<ftxui::Element> content;
    
    if (state.current_screen != ScreenState::ProblemAnalysis) {
        content.push_back(ftxui::text("select problem and press ENTER") |
                            ftxui::color(ftxui::Color::GrayDark));
    }
    else {
        content.push_back(ftxui::text(state.analysis.name) | ftxui::bold);
        content.push_back(ftxui::text("ID       : " + state.analysis.problem_id));
        content.push_back(ftxui::text("Rating    : " + std::to_string(state.analysis.rating)));
        content.push_back(ftxui::text("Tags     : " + join (state.analysis.tags, ", ")));
        content.push_back(ftxui::separator());
        content.push_back(ftxui::text("difficulty distribution") | ftxui::bold);

        for (const auto& [rating, count] : state.analysis.difficulty_distribution) {
            const int bar_width = std::min (30, std::max(1, count / 30));
            content.push_back(ftxui::hbox({
                ftxui::text(rating) | 
                ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 6),
                ftxui::text(std::string(bar_width, '#')) |
                ftxui::color(ftxui::Color::Green),
                ftxui::text(" " + std::to_string(count)),
            }));
        }

        content.push_back(ftxui::separator());
        content.push_back(ftxui::text("similar problems") | ftxui::bold);
        if (state.analysis.similar_problems.empty()) {
            content.push_back(ftxui::text("no similar problem found in cache"));
        }
        else {
            for (const auto& problem : state.analysis.similar_problems) {
                content.push_back(ftxui::text("-" + problem.problem_id + " " + problem.name));
            }
        }
    }

    return ftxui::vbox({
        ftxui::text("analysis") | 
        ftxui::bold,
        ftxui::separator(),
        ftxui::vbox(content) | 
        ftxui::yframe,
    }) | 
    ftxui::border | 
    ftxui::flex;
}

int main () {
    AppState state;
    auto screen = ftxui::ScreenInteractive::TerminalOutput();

    auto handle_input = ftxui::Input(&state.handle, "codeforces handle");
    auto start_button = ftxui::Button("START", [&] { fetchprob(state); });

    std::vector<std::string> menu_entries;
    auto menu = ftxui::Menu(&menu_entries, &state.selected_problem);

    auto layout = ftxui::Container::Vertical({
        ftxui::Container::Horizontal({
            menu,
            ftxui::Container::Vertical({
                handle_input, start_button,
            }),
        }),
    });

    auto component = ftxui::Renderer(layout, [&] {
        menu_entries.clear();
        for (const auto& problem : state.problems) {
            menu_entries.push_back(problem.problem_id + " " + problem.name + " [" + std::to_string(problem.rating) + "]");
        }

        ftxui::Element main_area;
        if (state.loading) {
            main_area = ftxui::vbox({
                ftxui::text("loading...") | 
                ftxui::bold,
                ftxui::text("fetch data from backend"),
            }) |
            ftxui::center |
            ftxui::border |
            ftxui::flex;
        } else {
            main_area = ftxui::hbox({
                problemlistpane(state),
                state.problems.empty() ? inputpane(handle_input, start_button, state) : analysispane(state), 
            });
        }

        return ftxui::vbox({
            ftxui::text("competitive programming submission explor") | 
            ftxui::bold |
            ftxui::color (ftxui::Color::Cyan),
            main_area | 
            ftxui::flex,
            statusline(state),
            helpbox(),
        }) | 
        ftxui::size(ftxui::HEIGHT, ftxui::GREATER_THAN, 28);
    });

    component = ftxui::CatchEvent(component, [&](ftxui::Event event) {
        if (event == ftxui::Event::Character('q') || event == ftxui::Event::Character('Q')) {
            screen.ExitLoopClosure()();
            return true;
        }
        if (event == ftxui::Event::Escape) {
            if (!state.problems.empty()) {
                state.current_screen = ScreenState::ProblemList;
                state.status = "back to problem list";
                return true;
            }
        }
        if (event == ftxui::Event::Return) {
            if (!state.problems.empty()) {
                analyzeselected(state);
                return true;
            }
        }
        return false;
    });

    screen.Loop(component);
    return 0;
}