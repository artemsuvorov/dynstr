#pragma once

#include <algorithm>

/// @brief Represents a read/write iterator for a dynamic string.
class CharIterator
{
public:
    using value_type = char;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;

public:
    CharIterator(char* pointer)
        : characters_pointer(pointer)
    { }

    CharIterator& operator++()
    {
        characters_pointer++;
        return *this;
    }

    CharIterator operator++(int)
    {
        CharIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    CharIterator& operator--()
    {
        characters_pointer--;
        return *this;
    }

    CharIterator operator--(int)
    {
        CharIterator iterator = *this;
        --(*this);
        return iterator;
    }

    char& operator[](int index)
    {
        return *(characters_pointer + index);
    }

    char* operator->()
    {
        return characters_pointer;
    }

    char& operator*()
    {
        return *characters_pointer;
    }

    bool operator==(const CharIterator& other) const
    {
        return characters_pointer == other.characters_pointer;
    }

    bool operator!=(const CharIterator& other) const
    {
        return !(*this == other);
    }

private:
    char* characters_pointer;
};