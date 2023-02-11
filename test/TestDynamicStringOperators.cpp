#pragma once

#include <gtest/gtest.h>

#include "DynamicString.h"

TEST(DynstrOperatorsTest, CopyAssignmentOperator)
{
    DynamicString apple = "Apple";
    DynamicString banana = "Banana";

    banana = apple;

    // expect that references do not equal
    EXPECT_NE(&apple, &banana);

    EXPECT_STREQ(apple.Characters(), "Apple");
    EXPECT_EQ(apple.Length(), 5);
    EXPECT_EQ(apple.Capacity(), 5);
    
    EXPECT_STREQ(banana.Characters(), "Apple");
    EXPECT_EQ(banana.Length(), 5);
    EXPECT_EQ(banana.Capacity(), 5);
}

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

TEST(DynstrOperatorsTest, MoveAssignmentOperator_WontMoveSelf)
{
    DynamicString apple = "Apple";
    apple = std::move(apple);

    EXPECT_NE(apple.Characters(), nullptr);

    EXPECT_STREQ(apple.Characters(), "Apple");
    EXPECT_EQ(apple.Length(), 5);
    EXPECT_EQ(apple.Capacity(), 5);
}

TEST(DynstrOperatorsTest, MoveAssignmentOperator_MoveSameData)
{
    DynamicString apple1 = "Apple";
    DynamicString apple2 = "Apple";

    // different objects but same data
    EXPECT_NE(&apple1, &apple2);

    apple2 = std::move(apple1);

    EXPECT_STREQ(apple2.Characters(), "Apple");
    EXPECT_EQ(apple2.Length(), 5);
    EXPECT_EQ(apple2.Capacity(), 5);

    // expects apple1 string to become a hollow object
    EXPECT_EQ(apple1.Characters(), nullptr);
    EXPECT_EQ(apple1.Length(), 0);
    EXPECT_EQ(apple1.Capacity(), 0);
}