cmake_minimum_required(VERSION 3.10)
project(project_doom)

set(CMAKE_CXX_STANDARD 17)  # Use C++17
set(CMAKE_CXX_FLAGS "-g -Wall")  # Debugging and warnings

file(GLOB SOURCES "*.cpp")
add_executable(doom ${SOURCES})