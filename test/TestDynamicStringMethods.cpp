#pragma once

#include <gtest/gtest.h>

#include "DynamicString.h"

TEST(DynstrMethodsTest, RemovesCharacter)
{
    DynamicString string = "He_&_llo!";
    string.Remove(2);
    string.Remove(2);
    string.Remove(2);

    EXPECT_STREQ(string.Characters(), "Hello!");
    EXPECT_EQ(string.Length(), 6);
    EXPECT_EQ(string.Capacity(), 9);
}

TEST(DynstrMethodsTest, Adds_And_Removes_And_Clears)
{
    DynamicString string;
    string.Concatenate("He");
    
    EXPECT_STREQ(string.Characters(), "He");
    EXPECT_EQ(string.Length(), 2);
    EXPECT_EQ(string.Capacity(), 2);

    string.Add('.');
    
    EXPECT_STREQ(string.Characters(), "He.");
    EXPECT_EQ(string.Length(), 3);
    EXPECT_EQ(string.Capacity(), 4);

    string.Concatenate("llo");
    
    EXPECT_STREQ(string.Characters(), "He.llo");
    EXPECT_EQ(string.Length(), 6);
    EXPECT_EQ(string.Capacity(), 6);

    string.Remove(2);
    
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 6);
    
    string.Clear();
    
    EXPECT_STREQ(string.Characters(), "");
    EXPECT_EQ(string.Length(), 0);
    EXPECT_EQ(string.Capacity(), 6);
}

TEST(DynstrMethodsTest, InsertsCharacter)
{
    DynamicString string = "Hllo";
    string.Insert(1, 'e');

    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 5);
}

TEST(DynstrMethodsTest, WontReserveOnSmallCapacity)
{
    DynamicString string = "Hello";
    string.Reserve(0);
    
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 5);

    string.Reserve(3); // 3 < strlen("Hello")
    
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 5);

    string.Reserve(5); 

    // capacity is already 5, so no effect
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 5);
}

TEST(DynstrMethodsTest, ReservesCapacity)
{
    DynamicString string = "Hello";
    string.Reserve(10);
    
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 10);
}

TEST(DynstrMethodsTest, NoAllocationsAfterReserve)
{
    DynamicString string;
    size_t expectedCapacity = string.Reserve(5);

    string.Add('.');
    string.Concatenate("Hi");
    string.Add('!');

    EXPECT_STREQ(string.Characters(), ".Hi!");
    EXPECT_EQ(string.Length(), 4);
    EXPECT_EQ(string.Capacity(), expectedCapacity);
}

TEST(DynstrMethodsTest, AllocatesAfterSmallReserve)
{
    DynamicString string;
    string.Reserve(3);

    string.Add('.');
    string.Concatenate("Hi");
    string.Add('!');

    EXPECT_STREQ(string.Characters(), ".Hi!");
    EXPECT_EQ(string.Length(), 4);
    EXPECT_EQ(string.Capacity(), 6);
}

TEST(DynstrMethodsTest, StringClears)
{
    DynamicString string = "Hello";
    string.Clear();
    
    EXPECT_STREQ(string.Characters(), "");
    EXPECT_EQ(string.Length(), 0);
    EXPECT_EQ(string.Capacity(), 5);
}

TEST(DynstrMethodsTest, StringEquals)
{
    DynamicString string = "Hello";
    DynamicString other = "Hello";
    DynamicString copy = string;

    EXPECT_TRUE(string.Equals("Hello"));
    EXPECT_TRUE(string.Equals(string));
    EXPECT_TRUE(string.Equals(other));
    EXPECT_TRUE(string.Equals(copy));
}

TEST(DynstrMethodsTest, StringDoesntEqual)
{
    DynamicString string = "Hello";
    DynamicString copy = string;
    copy.Concatenate("World");

    EXPECT_FALSE(string.Equals("!Hello"));
    EXPECT_FALSE(copy.Equals(string));
}