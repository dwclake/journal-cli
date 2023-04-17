cmake_minimum_required(VERSION 3.22)
project(pokedex)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_SOURCE_DIR includes)
set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/menu.h ${PROJECT_SOURCE_DIR}/src/menu.cpp)

add_executable(pokedex main.cpp ${SOURCE_FILES})
