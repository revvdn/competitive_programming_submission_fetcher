#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<memory>
#include<sstream>
#include<stdexcept>
#include<string>
#include<vector>
#include<chrono>
#include<thread>

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

std::vector<std::string> menu_entries;

const std::vector<std::string> spinner = {
    "⠋","⠙","⠹","⠸","⠼","⠴","⠦","⠧","⠇","⠏"
};

int spinner_frame = 0;

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
    if (item.contains("contestId")) {
        if (item["contestId"].is_number()) {
            prob.contest_id = std::to_string(item["contestId"].get<int>());
        } else {
            prob.contest_id = item["contestId"].get<std::string>();
        }
    }
    //prob.contest_id = item.value("contestId", 0);
    prob.index = item.value("index", "");
    prob.problem_id = item.value("problemId", prob.contest_id + prob.index);
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

void fetchprob (AppState& state, ftxui::ScreenInteractive& screen, ftxui::Component menu) {
    state.loading = true;
    state.current_screen = ScreenState::Loading;
    //state.error.clear();
    //state.status = "fetching solved problem";
    state.error.clear();
    state.status = "fetching solved problems";
    screen.Post(ftxui::Event::Custom);
    
    std::thread([&state, &screen, menu] {
        try {
            const std::string command = quote(pythoncommand()) + " " + quote(backendclipath()) + " --platform " + quote(state.platform) + " fetch " + quote(state.handle);
            
            std::string raw_output = runcommand(command);
            const auto payload = json::parse(raw_output);

            if (payload.value("status", "") != "success") 
                throw std::runtime_error(payload.value("error", "backend error"));

            screen.Post([&state, payload, &screen, menu] {
                state.problems.clear();
                for (const auto& item: payload.at("problems")) {
                    state.problems.push_back(parseproblem(item));
                }
                state.selected_problem = 0;
                state.status = " fetched " + std::to_string(state.problems.size()) + "solved problem";
                state.current_screen = ScreenState::ProblemList;
                state.loading = false;
                state.tab_selected = 1;
                menu->TakeFocus();
                screen.Post(ftxui::Event::Custom);
            });
        } catch (const std::exception& exc) {
            std::string error_msg = exc.what();
            screen.Post([&state, error_msg, &screen] {
                state.error = error_msg;
                state.status = "fetch_fail";
                state.current_screen = ScreenState::FetchForm;
                state.loading = false;
                state.tab_selected = 0;
                screen.Post(ftxui::Event::Custom);
            });
        }
    }).detach();
}


void analyzeselected (AppState& state, ftxui::ScreenInteractive& screen, ftxui::Component menu) {
    if (state.problems.empty())
        return;
    const Problem& selected = state.problems[state.selected_problem];
    state.error.clear();
    state.status = "analyze " + selected.problem_id + "...";

    std::string problem_id = selected.problem_id;
    std::string platform = state.platform;
    std::string name = selected.name;
    int selected_rating = selected.rating;

    screen.Post(ftxui::Event::Custom);

    std::thread([&state, &screen, menu, problem_id, platform, name, selected_rating]() {
        try {
            const std::string command = quote(pythoncommand()) + " " + quote(backendclipath()) + " --platform " + quote(platform) + " analyze " + quote(problem_id);

            const auto payload = json::parse(runcommand(command));

            if (payload.value("status", "") != "success")
                throw std::runtime_error(payload.value("error", "unkown backend error"));

            const auto& item = payload.at("analysis");
            Analysis analysis;
            analysis.problem_id = item.value("problemid", problem_id);
            analysis.name = item.value("name", "");
            analysis.rating = item.value("rating", 0);
            analysis.tags = tostringvector(item.value("tags", json::array()));
            analysis.same_rating_count = item.value("statisic", json::object()).value("same_rating_count", 0);
            
            for (const auto& similar : item.value("similar_problems", json::array())) {
                analysis.similar_problems.push_back(parseproblem(similar));
            }

            if (platform == "atcoder") {
                const auto atcoder_metrics = item.value("atcoder_metrics", json::object());
                analysis.solve_prob = atcoder_metrics.value("solve_prob", "");
                analysis.solve_time = atcoder_metrics.value("solve_time_mins", "");
            }

            const auto distribute = item.value("statistic", json::object()).value("difficulty_distribution", json::object());
            std::vector<std::pair<std::string , int>> temp_distribution;
            for (auto iter = distribute.begin(); iter != distribute.end(); iter++) {
                temp_distribution.push_back({iter.key(), iter.value().get<int>()});
            }

            screen.Post([&state, &screen, menu, analysis, temp_distribution, problem_id]() {
                state.analysis = analysis;
                state.analysis.difficulty_distribution = temp_distribution;
                state.status = "analysis for " + problem_id;
                state.current_screen = ScreenState::ProblemAnalysis;
                state.tab_selected = 1;
                menu -> TakeFocus();
                screen.Post(ftxui::Event::Custom);
            });
        } catch (const std::exception& exc) {
            std::string error_msg = exc.what();
            screen.Post([&state, &screen, error_msg] {
                state.error = error_msg;
                state.status = "analysis fail";
                screen.Post(ftxui::Event::Custom);
            });
        }
    }).detach();
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

ftxui::Element inputpane (ftxui::Component platform_toggle, ftxui::Component handle_input, ftxui::Component start_button, const AppState& state) {
    return ftxui::vbox({
        ftxui::text("input") | ftxui::bold,
        ftxui::separator(),
        ftxui::text("platform"),
        platform_toggle -> Render(),
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
        content.push_back(ftxui::text("select problem and press ENTER") | ftxui::color(ftxui::Color::GrayDark));
    }
    else {
        if (state.platform == "atcoder") {
            content.push_back(ftxui::text("Difficulty: " + std::to_string(state.analysis.rating)));
            content.push_back(ftxui::text("solve prob: " + state.analysis.solve_prob));
            content.push_back(ftxui::text("solve time: " + state.analysis.solve_time));
            content.push_back(ftxui::separator());
            content.push_back(ftxui::text("similar problem") | ftxui::bold);

            if (state.analysis.similar_problems.empty()) {
                content.push_back(ftxui::text("no similar problem found in cache"));
            } else {
                for (const auto& problem : state.analysis.similar_problems) {
                    content.push_back(ftxui::text("-" + problem.problem_id + " " + problem.name));
                }
            }
        } else {
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

    std::thread animation([&] {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(80));

            if (state.loading) {
                spinner_frame = (spinner_frame + 1) % spinner.size();
                screen.Post(ftxui::Event::Custom);
            }
        }
    });
    animation.detach();

    std::vector<std::string> platforms = {"codeforces", "atcoder"};
    int platform_selected = 0;
    auto platform_toggle = ftxui::Radiobox(&platforms, &platform_selected);


    auto handle_input = ftxui::Input(&state.handle, "handle");
    auto menu = ftxui::Menu(&menu_entries, &state.selected_problem);
    auto start_button = ftxui::Button("START", [&] { 
        state.platform = platforms[platform_selected];
        fetchprob(state, screen, menu); 
    });

    auto form_container = ftxui::Container::Vertical({
        platform_toggle,
        handle_input,
        start_button,
    });

    auto tab_container = ftxui::Container::Tab({
        form_container,
        ftxui::Renderer([] {return ftxui::text("");}),
    }, &state.tab_selected);

    auto layout = ftxui::Container::Vertical({
        ftxui::Container::Horizontal({
            menu,
            tab_container,
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
                ftxui::text(spinner[spinner_frame] + "loading...") | 
                ftxui::bold |
                ftxui::color(ftxui::Color::Green),

                //ftxui::text("fetching data from backend"),

                //ftxui::separator(),
                ftxui::text(state.status),
                ftxui::separator(),
                //ftxui::gauge((spinner_frame % 10 ) / 10.0f) /*| ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 40)*/,
                
            }) |
            ftxui::center |
            ftxui::border |
            ftxui::flex;
        } else {
            main_area = ftxui::hbox({
                problemlistpane(state),
                (state.current_screen == ScreenState::FetchForm) ? inputpane(platform_toggle, handle_input, start_button, state) : analysispane(state),
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
            if (state.current_screen == ScreenState::ProblemAnalysis) {
                state.current_screen = ScreenState::ProblemList;
                state.status = "back to problem list";
                state.tab_selected = 1;
                menu -> TakeFocus();
                return true;
            } else if (state.current_screen == ScreenState::ProblemList) {
                state.current_screen = ScreenState::FetchForm;
                state.status = "ready";
                state.tab_selected = 0;
                platform_toggle -> TakeFocus();
                return true;
            }
        }
        if (event == ftxui::Event::Return) {
            if (state.current_screen == ScreenState::ProblemList && !state.problems.empty()) {
                analyzeselected(state, screen, menu);
                return true;
            }
        }
        return false;
    });

    screen.Loop(component);
    return 0;
}