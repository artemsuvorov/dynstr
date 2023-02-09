# Windows:
# cmake -S . -B build/ -G "MinGW Makefiles"
# mingw32-make -C .\build\

cmake_minimum_required(VERSION 3.13)

project(dynstr VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(EXECUTABLE_OUTPUT_PATH "../../bin/")

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/gtest)