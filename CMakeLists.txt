cmake_minimum_required(VERSION 3.8)
project(QuadrisGame)

set(CMAKE_CXX_STANDARD 14)

find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

add_executable(
        QuadrisGame
        quadrisboard.h quadrisboard.cc
        main.cc
        cell.h cell.cc
        block.h block.cc
        level.cc level.h
        window.h window.cc
        interpreter.cc interpreter.h
        display.h display.cc
        )