cmake_minimum_required(VERSION 3.22)
project(journal-cli)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_DIR includes)
set(SOURCE_FILES ${SOURCE_DIR}/menu.h ${SOURCE_DIR}/src/menu.cpp 
                 ${SOURCE_DIR}/journal.h ${SOURCE_DIR}/src/journal.cpp
                 ${SOURCE_DIR}/page.h ${SOURCE_DIR}/src/page.cpp)

add_executable(journal-cli main.cpp ${SOURCE_FILES})
