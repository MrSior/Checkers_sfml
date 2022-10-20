cmake_minimum_required(VERSION 3.22)
project(Checkers)

set(CMAKE_CXX_STANDARD 17)

add_executable(Checkers main.cpp)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(Checkers sfml-graphics sfml-audio)
