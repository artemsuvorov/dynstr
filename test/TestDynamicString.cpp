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
    EXPECT_EQ(string.Capacity(), 2);
}

TEST(DynstrTest, ReallocatesMemory)
{
    DynamicString string;
    string.Add('A');
    string.Add('B');

    EXPECT_STREQ(string.Characters(), "AB");
    EXPECT_EQ(string.Length(), 2);
    EXPECT_EQ(string.Capacity(), 4);
}

TEST(DynstrTest, CreateFromConstChar)
{
    DynamicString string = "Hello";
    
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 6);
}

TEST(DynstrTest, ModifiesCharacter)
{
    DynamicString string = "Henlo";
    string[2] = 'l';
    
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 6);
}

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
    EXPECT_EQ(string.Capacity(), 6);
}

TEST(DynstrConcatTest, ConcatWithEmptyString)
{
    DynamicString string = "Hello";
    string.Concatenate("");
    
    EXPECT_STREQ(string.Characters(), "Hello");
    EXPECT_EQ(string.Length(), 5);
    EXPECT_EQ(string.Capacity(), 6);
}

TEST(DynstrConcatTest, ConcatHelloWorld)
{
    DynamicString string = "Hello,";
    string.Concatenate(" World!");
    
    EXPECT_STREQ(string.Characters(), "Hello, World!");
    EXPECT_EQ(string.Length(), 13);
    EXPECT_EQ(string.Capacity(), 14);
}