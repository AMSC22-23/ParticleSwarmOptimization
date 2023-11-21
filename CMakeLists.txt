cmake_minimum_required(VERSION 3.20)
project(PSO)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(PSO_EXEC ${SOURCES})