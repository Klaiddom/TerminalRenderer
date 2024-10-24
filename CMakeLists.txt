cmake_minimum_required(VERSION 3.10)

project(TerminalRenderer VERSION 0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HEADERS headers/screen.h)
set(SOURCES src/screen.cpp)

add_executable(TerminalRenderer main.cpp ${HEADERS} ${SOURCES})