#pragma once

#include <cstddef>
#include <assert.h>
#include <memory>

#include <iostream>

/// @brief A dynamic string for managing sequences of characters.
class DynamicString
{
public:
    /// @brief Default constructor that creates an empty string.
    DynamicString() 
    {
        Reallocate(1);
        characters[0] = '\0';
    }

    /// @brief Destroy the string instance.
    ~DynamicString() { delete[] characters; }

public:
    /// @brief Adds the specified character at the end of 
    /// the string before the null-terminating character.
    /// @param character The character to be added to the string.
    void Add(char character)
    {
        std::cout << "Adding: " << character << std::endl;

        if (length + 1 >= capacity)
            Reallocate(GROWTH_FACTOR * capacity);

        characters[length] = character;
        characters[length + 1] = '\0';

        std::cout << "Length: " << length+1 << " / capacity: " << capacity << std::endl;
        std::cout << characters[length] << std::endl;
        length++;
    }

    /// @brief Returns the number of characters within the string 
    /// without a null-terminating character.
    /// @return The number of characters within the string 
    /// without a null-terminating character.
    size_t Length() const { return length; }

    /// @brief Returns const pointer to null-terminated contents of the string.
    /// @return Const pointer to null-terminated contents of the string.
    const char* Characters() const { return characters; }

public:
    /// @brief Returns a character of a string at the specified index.
    /// @param index The index within the string at which the character will be returned. 
    /// @return Character of a string at the specified index.
    const char& operator[](size_t index) const
    {
        assert(index < length);
        return characters[index];
    }

    /// @brief Returns a character of a string at the specified index.
    /// @param index The index within the string at which the character will be returned. 
    /// @return Character of a string at the specified index.
    char& operator[](size_t index)
    {
        assert(index < length);
        return characters[index];
    }

private:
    /// @brief Allocates a new block of memory and moves all 
    /// the existing elements into this new block.
    /// @param newCapacity The capacity of the new block of memory.
    void Reallocate(size_t newCapacity)
    {
        std::cout << "Reallocating !!!" << std::endl;
        char* newCharacters = new char[newCapacity];
        length = newCapacity < length ? newCapacity : length; 
        // copying all the chars before the null-terminated character
        memcpy(newCharacters, characters, length * sizeof(char));
        delete[] characters;
        characters = newCharacters;
        capacity = newCapacity;
    }

private:
    static const size_t GROWTH_FACTOR = 2;

    char* characters = nullptr;
    size_t length = 0;
    size_t capacity = 0;
};