cmake_minimum_required(VERSION 3.22)
project(diary-cli)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_DIR includes)
set(SOURCE_FILES ${SOURCE_DIR}/menu.h ${SOURCE_DIR}/src/menu.cpp 
                 ${SOURCE_DIR}/clist.h ${SOURCE_DIR}/src/clist.cpp)

add_executable(diary-cli main.cpp ${SOURCE_FILES})
