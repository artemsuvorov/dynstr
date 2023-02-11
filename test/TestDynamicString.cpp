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

TEST(DynstrConcatTest, ConcatHelloWorld)
{
    DynamicString string = "Hello,";
    string.Concatenate(" World!");
    
    EXPECT_STREQ(string.Characters(), "Hello, World!");
    EXPECT_EQ(string.Length(), 13);
    EXPECT_EQ(string.Capacity(), 13);
}