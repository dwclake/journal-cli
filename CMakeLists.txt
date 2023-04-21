cmake_minimum_required(VERSION 3.22)
project(journal-cli)

set(CMAKE_CXX_STANDARD 20)

set(INCLUDES_DIR includes)
set(SOURCE_DIR src)
set(TEST_DIR test)
set(SOURCE_FILES ${INCLUDES_DIR}/menu/menu.h ${SOURCE_DIR}/menu/menu.cpp 
                 ${INCLUDES_DIR}/journal/journal.h ${SOURCE_DIR}/journal/journal.cpp
                 ${INCLUDES_DIR}/journal/page.h ${SOURCE_DIR}/journal/page.cpp)
set(TEST_FILES ${TEST_DIR}/test.h ${TEST_DIR}/test.cpp)

add_executable(journal-cli src/main.cpp ${INCLUDES_DIR} ${SOURCE_FILES} ${TEST_FILES})
