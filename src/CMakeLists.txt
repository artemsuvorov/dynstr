set(CMAKE_CXX_STANDARD 11)

set(
    SOURCES 
    main.cpp
    DynamicString.h
    DynamicString.cpp
    DynamicStringIterator.h
    DynamicStringComparator.h
)

add_executable(
    ${CMAKE_PROJECT_NAME}
    ${SOURCES}
)

add_library(
    ${CMAKE_PROJECT_NAME}lib
    STATIC
    ${SOURCES}
)