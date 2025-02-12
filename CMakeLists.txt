cmake_minimum_required(VERSION 3.10)
project(project_doom)

set(CMAKE_CXX_STANDARD 17)  # Use C++17
set(CMAKE_CXX_FLAGS "-g -Wall")  # Debugging and warnings

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "*.cpp")  # Get all .cpp files in the directory
add_executable(doom ${SOURCES})  # Define executable first

target_link_libraries(doom ${SDL2_LIBRARIES})  # Link SDL2 after defining the executable