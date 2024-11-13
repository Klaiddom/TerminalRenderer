cmake_minimum_required(VERSION 3.10)

project(TerminalRenderer VERSION 0.0)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HEADERS headers/screen.h)
set(SOURCES src/screen.cpp)

add_executable(TerminalRenderer main.cpp ${HEADERS} ${SOURCES})

target_link_libraries(TerminalRenderer ${OpenCV_LIBS})