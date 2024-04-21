cmake_minimum_required(VERSION 3.27)
project(lab23 C)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig)
pkg_check_modules(cstruct REQUIRED IMPORTED_TARGET cstruct)

FILE(GLOB SOURCES
        "include/*.h"
        "src/*.c")
include_directories("include/")
add_executable(lab23 ${SOURCES})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g ")
target_link_libraries(lab23 PUBLIC PkgConfig::cstruct)
target_include_directories(lab23 PUBLIC PkgConfig::cstruct)



