#pragma once

#include <gtest/gtest.h>

#include "DynamicString.h"

TEST(DynstrOperatorsTest, MoveAssignmentOperator)
{
    DynamicString apple = "Apple";
    DynamicString banana = "Banana";
    banana = std::move(apple);

    EXPECT_STREQ(banana.Characters(), "Apple");
    EXPECT_EQ(banana.Length(), 5);
    EXPECT_EQ(banana.Capacity(), 5);

    // expects apple string to become a hollow object
    EXPECT_EQ(apple.Characters(), nullptr);
    EXPECT_EQ(apple.Length(), 0);
    EXPECT_EQ(apple.Capacity(), 0);
}