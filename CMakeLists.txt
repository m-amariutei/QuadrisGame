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
        BlockClasses/Iblock.h BlockClasses/Iblock.cc
        BlockClasses/Jblock.h BlockClasses/Jblock.cc
        BlockClasses/Lblock.h BlockClasses/Lblock.cc
        BlockClasses/Oblock.h BlockClasses/Oblock.cc
        BlockClasses/Sblock.h BlockClasses/Sblock.cc
        BlockClasses/Tblock.h BlockClasses/Tblock.cc
        BlockClasses/Zblock.h BlockClasses/Zblock.cc
        )