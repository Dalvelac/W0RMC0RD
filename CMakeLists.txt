cmake_minimum_required(VERSION 3.14)
project(DiscordWormSimulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(CPR_USE_SYSTEM_CURL ON)

# cpr
FetchContent_Declare(
  cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG 1.10.5
)
FetchContent_MakeAvailable(cpr)

# nlohmann json
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)

# Catch2
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_library(worm
    src/TokenLoader.cpp
    src/WormLogic.cpp
    src/RateLimiter.cpp
    src/Logger.cpp
    src/KillSwitch.cpp
)

target_include_directories(worm PUBLIC include)

target_link_libraries(worm PUBLIC cpr::cpr nlohmann_json::nlohmann_json spdlog::spdlog)

add_executable(simulator src/main.cpp)
target_link_libraries(simulator PRIVATE worm)

# Tests
enable_testing()
add_executable(tests
    tests/TokenLoaderTests.cpp
    tests/RateLimiterTests.cpp
    tests/KillSwitchTests.cpp
    tests/WormLogicTests.cpp
)

target_link_libraries(tests PRIVATE worm Catch2::Catch2WithMain)
add_test(NAME allTests COMMAND tests)

