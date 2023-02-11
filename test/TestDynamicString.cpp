#pragma once

#include <gtest/gtest.h>

#include "DynamicString.h"

TEST(DynstrTest, IsEmptyOnInit)
{
    DynamicString string;

    EXPECT_STREQ(string.Characters(), "");
    EXPECT_EQ(string.Length(), 0);
    EXPECT_EQ(string.Capacity(), 1);
}

TEST(DynstrTest, AddsSingleCharacter)
{
    DynamicString string;
    string.Add('A');

    EXPECT_STREQ(string.Characters(), "A");
    EXPECT_EQ(string.Length(), 1);
    EXPECT_EQ(string.Capacity(), 1);
}

TEST(DynstrTest, ReallocatesMemory)
{
    DynamicString string;
    size_t initialCapacity = string.Capacity();

    string.Add('A');
    string.Add('B');
    size_t newCapacity = string.Capacity();

    EXPECT_STREQ(string.Characters(), "AB");
    EXPECT_EQ(string.Length(), 2);
    EXPECT_EQ(string.Capacity(), 2);

    EXPECT_GT(newCapacity, initialCapacity);
}

TEST(DynstrTest, CreateFromConstChar)
{
    DynamicString string = "Hello";
    
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 5);
}

TEST(DynstrTest, ModifiesCharacter)
{
    DynamicString string = "Henlo";
    string[2] = 'l';
    
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 5);
}

TEST(DynstrTest, StringCopies)
{
    DynamicString first = "Hello";
    DynamicString second = first;

    second[1] = 'a';
    
    EXPECT_STREQ(first.Characters(), "Hello");
    EXPECT_EQ(first.Length(), 5);
    EXPECT_EQ(first.Capacity(), 5);
    
    EXPECT_STREQ(second.Characters(), "Hallo");
    EXPECT_EQ(second.Length(), 5);
    EXPECT_EQ(second.Capacity(), 5);
}