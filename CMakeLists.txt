cmake_minimum_required(VERSION 3.16)
project(Lab02_String_Variant7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

if(ENABLE_ASAN)
    if(MSVC)
        add_compile_options(/fsanitize=address)
    else()
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    endif()
endif()

add_library(lab_string src/str.cpp)
target_include_directories(lab_string PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if(MSVC)
    target_compile_options(lab_string PRIVATE /W4)
else()
    target_compile_options(lab_string PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(lab02 src/main.cpp)
target_link_libraries(lab02 PRIVATE lab_string)

include(CTest)

if(BUILD_TESTING)
    find_package(GTest QUIET)
    if(NOT GTest_FOUND)
        include(FetchContent)
        if(POLICY CMP0135)
            cmake_policy(SET CMP0135 NEW)
        endif()
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_Declare(googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
            URL_HASH SHA256=f179ec217f9b3b3f3c6e8b02d3e7eda997b49e4ce26d6b235c9053bec9c0bf9f
        )
        FetchContent_MakeAvailable(googletest)
    endif()

    add_executable(test_string tests/test_string.cpp)
    if(TARGET GTest::gtest_main)
        target_link_libraries(test_string PRIVATE lab_string GTest::gtest_main)
    else()
        target_link_libraries(test_string PRIVATE lab_string GTest::Main)
    endif()
    include(GoogleTest)
    gtest_discover_tests(test_string)
endif()
