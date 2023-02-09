#pragma once

#include <assert.h>
#include <cstring>

// #include <iostream>

/// @brief A dynamic string for managing sequences of characters.
class DynamicString
{
public:
    /// @brief Default constructor that creates an empty string.
    DynamicString() : DynamicString("") { }

    /// @brief Constructor that creates a string consisting of 
    /// the specified characters.
    /// @param value The character sequence to be put in the string.
    DynamicString(const char* value)
    {
        SetCharacters(value);
    }

    /// @brief Destroy the string instance.
    ~DynamicString() { delete[] characters; }

public:
    /// @brief Adds the specified character at the end of 
    /// the string before the null-terminating character.
    /// @param character The character to be added to the string.
    void Add(char character)
    {
        if (length + 1 >= capacity)
            Reallocate(GROWTH_FACTOR * capacity);

        // std::cout << character << " -> ";
        // for (int i = 0; i < capacity; i++)
        //     std::cout << (characters[i] == 0 ? '.' : characters[i]) << " ";
        // std::cout << "(len = " << length << ")" << " (cap = " << capacity << ")" << std::endl;
        characters[length] = character;
        characters[length + 1] = '\0';
        length++;
    }

    void Concatenate(const char* value)
    {
        size_t valueLength = strlen(value);
        size_t newLength = length + valueLength;
        if (newLength + 1>= capacity)
            Reallocate(newLength + 1);

        memcpy(characters + length, value, valueLength + 1);
        length = newLength;
    }

    /// @brief Returns the number of characters within the string 
    /// without a null-terminating character.
    /// @return The number of characters within the string 
    /// without a null-terminating character.
    size_t Length() const { return length; }

    /// @brief Returns the current capacity of the dynamic string.
    /// @return The current capacity of the dynamic string.
    size_t Capacity() const { return capacity; }

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
    /// @brief Assings the specified char sequence as the new data 
    /// for the dynamic string. 
    /// @param value The char sequence to be assigned.
    void SetCharacters(const char* value)
    {
        length = strlen(value);
        char* newCharacters = new char[length + 1];
        memcpy(newCharacters, value ? value : "", (length + 1) * sizeof(char));
        characters = newCharacters;
        capacity = capacity < length + 1 ? length + 1 : capacity;
    }

    /// @brief Allocates a new block of memory and moves all 
    /// the existing elements into this new block.
    /// @param newCapacity The capacity of the new block of memory.
    void Reallocate(size_t newCapacity)
    {
        // std::cout << "Reallocating !!!" << std::endl;
        char* newCharacters = new char[newCapacity];
        memcpy(newCharacters, characters ? characters : "", (length + 1) * sizeof(char));
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