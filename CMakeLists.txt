cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(review LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(matchit CONFIG REQUIRED)

set(LIBS fmt::fmt 
         range-v3::meta range-v3::concepts range-v3::range-v3
         matchit::matchit)

set(INCLUDE_DIR include)
set(SOURCE_DIR source)
set(TEST_DIR test)

set(INCLUDE_FILES ${INCLUDE_DIR}/app/menu.hpp
                  ${INCLUDE_DIR}/journal/journal.hpp
                  ${INCLUDE_DIR}/journal/page.hpp
                  ${INCLUDE_DIR}/utility/utility.hpp
                  ${INCLUDE_DIR}/input/input.hpp)

set(SOURCE_FILES  ${SOURCE_DIR}/app/menu.cxx 
                  ${SOURCE_DIR}/journal/journal.cxx
                  ${SOURCE_DIR}/journal/page.cxx
                  ${SOURCE_DIR}/utility/utility.cxx
                  ${SOURCE_DIR}/input/input.hpp)

set(TEST_FILES    ${TEST_DIR}/journal/journal_test.hpp
                  ${TEST_DIR}/journal/journal_test.cxx)

add_executable(review ${SOURCE_DIR}/main.cxx 
                      ${INCLUDE_FILES} 
                      ${SOURCE_FILES})
target_link_libraries(review PRIVATE ${LIBS})

add_executable(review-test ${TEST_DIR}/test.cxx 
                           ${TEST_FILES} 
                           ${INCLUDE_FILES} 
                           ${SOURCE_FILES})
target_link_libraries(review-test PRIVATE ${LIBS})

enable_testing()

add_test(
    NAME journal-test
    COMMAND $<TARGET_FILE:review-test> --journal
)
