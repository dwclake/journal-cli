cmake_minimum_required(VERSION 3.22)
project(journal-cli)

set(CMAKE_CXX_STANDARD 20)

set(INCLUDES_DIR includes)
set(SOURCE_DIR src)
set(TEST_DIR test)

set(INCLUDES_FILES ${INCLUDES_DIR}/menu/menu.h
                   ${INCLUDES_DIR}/journal/journal.h
                   ${INCLUDES_DIR}/journal/page.h)

set(SOURCE_FILES  ${SOURCE_DIR}/menu/menu.cpp 
                  ${SOURCE_DIR}/journal/journal.cpp
                  ${SOURCE_DIR}/journal/page.cpp)

set(TEST_FILES ${TEST_DIR}/test.h 
               ${TEST_DIR}/test.cpp)

add_executable(journal-cli src/main.cpp ${INCLUDES_FILES} ${SOURCE_FILES} ${TEST_FILES})
