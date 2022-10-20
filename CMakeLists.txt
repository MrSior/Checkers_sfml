cmake_minimum_required(VERSION 3.22)
project(Checkers)

set(CMAKE_CXX_STANDARD 17)

add_executable(Checkers main.cpp AppModel/AppModel.cpp AppModel/AppModel.h AppRender/AppRender.cpp AppRender/AppRender.h AppController/AppController.cpp AppController/AppController.h)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(Checkers sfml-graphics sfml-audio)
