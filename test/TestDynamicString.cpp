#include <gtest/gtest.h>

#include "DynamicString.h"

TEST(DynstrTest, DynamicString_IsEmpty_OnInit)
{
    DynamicString string;

    EXPECT_STREQ(string.Characters(), "");
    EXPECT_EQ(string.Length(), 0);
    EXPECT_EQ(string.Capacity(), 1);
}