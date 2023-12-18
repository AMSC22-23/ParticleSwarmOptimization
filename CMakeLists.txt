cmake_minimum_required(VERSION 3.20)
project(PSO)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(PSO_EXEC ${SOURCES})