cmake_minimum_required(VERSION 3.16)
project(FiguresLab4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(FiguresLab4 
    main.cpp
)

find_package(GTest REQUIRED)

add_executable(tests 
    test.cpp
)
target_link_libraries(tests GTest::gtest GTest::gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(tests)
