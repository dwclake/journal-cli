cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "Vcpkg toolchain file")

project(journal-cli)

set(CMAKE_CXX_STANDARD 23)

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
                  ${INCLUDE_DIR}/utility/utility.hpp)

set(SOURCE_FILES  ${SOURCE_DIR}/app/menu.cxx 
                  ${SOURCE_DIR}/journal/journal.cxx
                  ${SOURCE_DIR}/journal/page.cxx
                  ${SOURCE_DIR}/utility/utility.cxx)

set(TEST_FILES ${TEST_DIR}/test.hpp 
               ${TEST_DIR}/test.cxx)

add_executable(journal-cli ${SOURCE_DIR}/main.cxx ${INCLUDE_FILES} ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(journal-cli PRIVATE ${LIBS})
