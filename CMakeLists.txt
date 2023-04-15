cmake_minimum_required(VERSION 3.22)
project(pokedex)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_SOURCE_DIR src)
set(SOURCE_FILES ${PROJECT_SOURCE_DIR})

add_executable(pokedex ${PROJECT_SOURCE_DIR}/main.cpp ${SOURCE_FILES})
