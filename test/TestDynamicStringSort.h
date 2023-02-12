#pragma once

#include <gtest/gtest.h>
#include <vector>
#include <array>

#include "DynamicString.h"
#include "DynamicStringComparator.h"

TEST(DynstrSortTest, SortsReverseLexigocraphically_CaseInsensitive)
{
    std::array<DynamicString, 8> actual = {
        "Unix",
        "WIN32",
        "Apple",
        "MAC",
        "Microsoft",
        "google",
        "AWK",
        "C++",
    };

    const std::array<DynamicString, 8> expected = {
        "WIN32",
        "Unix",
        "Microsoft",
        "MAC",
        "google",
        "C++",
        "AWK",
        "Apple",
    };
    
    std::sort(actual.begin(), actual.end(),
        DynamicStringComparator::Lexicographical_Reversed_CaseInsensitive);

    ASSERT_EQ(expected.size(), actual.size());

    for (size_t i = 0; i < actual.size(); i++)
        EXPECT_EQ(expected[i], actual[i]) << "Arrays differ at index " << i;
}