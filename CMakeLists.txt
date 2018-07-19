cmake_minimum_required(VERSION 3.10)
project(QuadrisGame)

set(CMAKE_CXX_STANDARD 14)

find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

add_executable(QuadrisGame main.cc block.h block.cc quadrisboard.h quadrisboard.cc level.cc level.h cell.h cell.cc window.h window.cc)