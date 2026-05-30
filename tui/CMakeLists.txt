cmake_minimum_required(VERSION 3.20)

project(CPSE_TUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v5.0.0
)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(ftxui nlohmann_json)

get_filename_component(CPSE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)

add_executable(cpse_tui
  app/main.cpp
)

target_include_directories(cpse_tui PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/app"
)

target_compile_definitions(cpse_tui PRIVATE
  CPSE_PROJECT_ROOT="${CPSE_ROOT}"
)

target_link_libraries(cpse_tui PRIVATE
  ftxui::screen
  ftxui::dom
  ftxui::component
  nlohmann_json::nlohmann_json
)
