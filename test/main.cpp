#include <gtest/gtest.h>

#include "TestDynamicString.h"
#include "TestDynamicStringMethods.h"
#include "TestDynamicStringConcat.h"
#include "TestDynamicStringOperators.h"

#include "TestDynamicStringSort.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}