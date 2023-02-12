#pragma once

#include <algorithm>
#include <cctype>

#include "DynamicString.h"

/// @brief Represents a static class that provides functors to sort dynamic strings.
class DynamicStringComparator
{
public:
    static bool Lexicographical_Reversed_CaseInsensitive(
        const DynamicString& first, const DynamicString& second)
    {
        using Iterator = DynamicString::Iterator;
        return std::lexicographical_compare(
            first.begin(), first.end(),
            second.begin(), second.end(),
            [](char lhs, char rhs) { 
                return std::tolower(lhs) > std::tolower(rhs);
            }
        );
    }
};