set(CMAKE_CXX_STANDARD 14)

set(BINARY test-${CMAKE_PROJECT_NAME})
set(
    SOURCES
    main.cpp
    TestDynamicString.h
    TestDynamicStringConcat.h
    TestDynamicStringMethods.h
    TestDynamicStringOperators.h
    TestDynamicStringSort.h
)

add_executable(
    ${BINARY}
    ${SOURCES}
)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(
    ${BINARY} 
    PUBLIC 
    ${CMAKE_PROJECT_NAME}lib 
    gtest
)