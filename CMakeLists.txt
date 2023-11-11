cmake_minimum_required(VERSION 3.13)

project(rubiks_cube_app LANGUAGES CXX)

# Get googletest
include(FetchContent)
FetchContent_Declare(googletest 
                    GIT_REPOSITORY https://github.com/google/googletest 
                    GIT_TAG release-1.11.0)

# Get variables populated, source_dir and build_dir
FetchContent_GetProperties(googletest)

# Verify if already downloaded googletest
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

include_directories(include)

add_library(cube src/cube.cpp src/piecesmapping.cpp src/rotation.cpp)
add_library(lehmercode src/lehmercode.cpp)
add_library(pruner src/pruningtables.cpp src/indexer.cpp src/lehmercode.cpp)
add_library(solver src/solver.cpp src/utils.cpp)

add_executable(test_cube tests/cube_test.cpp)
target_link_libraries(test_cube cube gtest_main gmock_main)

add_executable(test_lehmercode tests/lehmercode_test.cpp)
target_link_libraries(test_lehmercode lehmercode gtest_main gmock_main)

add_executable(test_rotator tests/rotator_test.cpp)
target_link_libraries(test_rotator cube gtest_main gmock_main)

add_executable(test_pruner tests/pruner_test.cpp)
target_link_libraries(test_pruner pruner cube gtest_main gmock_main)

add_executable(test_solver tests/solver_test.cpp)
target_link_libraries(test_solver solver pruner cube gtest_main gmock_main)

add_executable(main src/main.cpp)
target_link_libraries(main solver pruner cube)