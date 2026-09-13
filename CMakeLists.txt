cmake_minimum_required(VERSION 3.25)

project(market_replay
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_library(market_replay_lib
    src/market_data_reader.cpp
    src/market_replay.cpp
    src/market_statistics.cpp
)

target_include_directories(market_replay_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(market_replay
    src/main.cpp
)

# Experiments
add_executable(object_layout
    experiments/object_layout.cpp
)

target_link_libraries(object_layout
    PRIVATE
    market_replay_lib
)

add_executable(vector_growth
    experiments/vector_growth.cpp
)

target_link_libraries(vector_growth
    PRIVATE
    market_replay_lib
)

add_executable(vector_reserve
    experiments/vector_reserve.cpp
)

target_link_libraries(vector_reserve
    PRIVATE
    market_replay_lib
)

add_executable(copy_vs_reference
    experiments/copy_vs_reference.cpp
)

target_link_libraries(copy_vs_reference
    PRIVATE
    market_replay_lib
)

add_executable(assembly_demo
    experiments/assembly_demo.cpp
)

target_link_libraries(assembly_demo
    PRIVATE
    market_replay_lib
)

target_link_libraries(market_replay
    PRIVATE
        market_replay_lib
)

add_executable(market_replay_tests
    tests/test_market_replay.cpp
)

target_link_libraries(market_replay_tests
    PRIVATE
        market_replay_lib
        Catch2::Catch2WithMain
)

target_compile_features(market_replay_tests
    PRIVATE
        cxx_std_23
)

include(CTest)
include(Catch)

catch_discover_tests(
    market_replay_tests
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)