#include <gtest/gtest.h>

#include "TestDynamicString.cpp"
#include "TestDynamicStringMethods.cpp"
#include "TestDynamicStringConcat.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}