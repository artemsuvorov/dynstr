#pragma once

#include <gtest/gtest.h>

#include "DynamicString.h"

TEST(DynstrConcatTest, ConcatEmptyStrings)
{
    DynamicString string;
    string.Concatenate("");
    
    EXPECT_STREQ(string.Characters(), "");
    EXPECT_EQ(string.Length(), 0);
    EXPECT_EQ(string.Capacity(), 1);
}

TEST(DynstrConcatTest, ConcatToEmptyString)
{
    DynamicString string;
    string.Concatenate("Hello");
    
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 5);
}

TEST(DynstrConcatTest, ConcatWithEmptyString)
{
    DynamicString string = "Hello";
    string.Concatenate("");
    
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 5);
}

TEST(DynstrConcatTest, ConcatWithNullptr)
{
    DynamicString string = "Hello";
    string.Concatenate(nullptr);
    
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 5);
}

TEST(DynstrConcatTest, ConcatHelloWorld)
{
    DynamicString string = "Hello,";
    string.Concatenate(" World!");
    
    EXPECT_STREQ(string.Characters(), "Hello, World!");
    EXPECT_EQ(string.Length(), 13);
    EXPECT_EQ(string.Capacity(), 13);
}