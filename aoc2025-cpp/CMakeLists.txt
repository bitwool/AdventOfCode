cmake_minimum_required(VERSION 3.26)
project(AdventOfCode2025 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_SANITIZERS "Enable address and undefined sanitizers" OFF)

file(GLOB_RECURSE AOC_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(aoc2025 ${AOC_SOURCES})

target_include_directories(aoc2025 PRIVATE src)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(aoc2025 PRIVATE /permissive- /W4 /WX)
else()
  target_compile_options(aoc2025 PRIVATE -Wall -Wextra -Wpedantic -Werror -Wconversion -Wshadow)
  if(ENABLE_SANITIZERS)
    target_compile_options(aoc2025 PRIVATE -fsanitize=address,undefined)
    target_link_options(aoc2025 PRIVATE -fsanitize=address,undefined)
  endif()
endif()

install(TARGETS aoc2025 RUNTIME DESTINATION bin)
