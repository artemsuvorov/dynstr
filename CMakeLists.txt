cmake_minimum_required(VERSION 3.13)

project(dynstr VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(EXECUTABLE_OUTPUT_PATH "../bin/")

# set(EXTERNAL_LIB_HEADERS "lib/gtest")

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/DynamicString.cpp
)

# target_include_directories(
#     ${PROJECT_NAME} PRIVATE
#     ${EXTERNAL_LIB_HEADERS}
# )