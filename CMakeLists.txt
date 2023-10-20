cmake_minimum_required(VERSION 3.13)

project(converter LANGUAGES CXX)

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

include_directories(src include tests)

add_library(converter STATIC src/converter.cpp)

add_executable(main src/main.cpp)
target_link_libraries(main converter)

add_executable(converter_test tests/converter_test.cpp)
target_link_libraries(converter_test converter gtest_main gmock_main)