cmake_minimum_required(VERSION 3.24)

set(DCMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project(journal-cli)

set(CMAKE_CXX_STANDARD 20)

find_package(unofficial-sqlite3 CONFIG REQUIRED)

set(LIBS unofficial::sqlite3::sqlite3)

set(INCLUDE_DIR include)
set(SOURCE_DIR source)
set(TEST_DIR test)

set(INCLUDE_FILES ${INCLUDE_DIR}/app/menu.h
                  ${INCLUDE_DIR}/journal/journal.h
                  ${INCLUDE_DIR}/journal/page.h
                  ${INCLUDE_DIR}/utility/utility.h)

set(SOURCE_FILES  ${SOURCE_DIR}/app/menu.cpp 
                  ${SOURCE_DIR}/journal/journal.cpp
                  ${SOURCE_DIR}/journal/page.cpp
                  ${SOURCE_DIR}/utility/utility.cpp)

set(TEST_FILES ${TEST_DIR}/test.h 
               ${TEST_DIR}/test.cpp)

add_executable(journal-cli ${SOURCE_DIR}/main.cpp ${INCLUDE_FILES} ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(journal-cli PRIVATE ${LIBS})
