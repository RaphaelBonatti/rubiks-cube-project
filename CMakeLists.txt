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

add_library(representer src/computationalrepresentation.cpp src/piecesmapping.cpp src/facerotations.cpp)
add_library(pruner src/pruningtables.cpp)

# add_library(converter src/converter.cpp src/computationalrepresentation.cpp src/piecesmapping.cpp)
# add_library(solver src/solver.cpp src/facerotations.cpp)

# add_executable(${PROJECT_NAME} src/main.cpp)
# target_link_libraries(${PROJECT_NAME} converter solver)

add_executable(test_converter tests/converter_test.cpp)
target_link_libraries(test_converter representer gtest_main gmock_main)

add_executable(test_solver tests/solver_test.cpp)
target_link_libraries(test_solver representer gtest_main gmock_main)

add_executable(test_pruner tests/pruner_test.cpp)
target_link_libraries(test_pruner pruner gtest_main gmock_main)