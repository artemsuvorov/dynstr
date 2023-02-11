#pragma once

#include <assert.h>
#include <cstring>

// TODO: get rid of all of the useless comments
#include <iostream>

#define DEBUG

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
        // for the debug purposes
        std::cout << "Created!" << std::endl;
    }

    /// @brief A copy constructor that creates a copy of another dynamic string.
    /// @param other The string to be copied.
    DynamicString(const DynamicString& other) 
    {
        DeepCopyFrom(other);
    }

    /// @brief A move constructor that moves an rvalue object of the specified dynamic string.
    /// @param other The string to be moved.
    DynamicString(DynamicString&& other) noexcept
    {
        ShallowCopyFrom(std::move(other));
    }

    /// @brief Destroy the dynamic string instance.
    ~DynamicString() 
    { 
        delete[] characters;
        // for the debug purposes
        std::cout << "Destroyed!" << std::endl;
    }

public:
    /// @brief Adds the specified character at the end of 
    /// the string before the null-terminating character.
    /// @param character The character to be added to the string.
    void Add(char character)
    {
        if (length + 1 > capacity)
            Reallocate(GROWTH_FACTOR * capacity);

        // std::cout << character << " -> ";
        // for (int i = 0; i < capacity; i++)
        //     std::cout << (characters[i] == 0 ? '.' : characters[i]) << " ";
        // std::cout << "(len = " << length << ")" << " (cap = " << capacity << ")" << std::endl;
        characters[length] = character;
        characters[length + 1] = '\0';
        length++;
    }

    /// @brief Concatenates the specified string to the dynamic string.
    /// @param value The string to be concatenated.
    void Concatenate(const char* value)
    {
        size_t valueLength = strlen(value);
        size_t newLength = length + valueLength;
        // std::cout << length << " " << valueLength << " => " << (newLength + newLength % 2) << std::endl;
        if (newLength > capacity)
            // Reallocate(newLength + newLength % 2);
            Reallocate(newLength);

        //strcpy(characters + length, value);
        memcpy(characters + length, value, (valueLength + 1) * sizeof(char));
        length = newLength;
    }

    /// @brief Removes a character from the dynamic string at the specified index.
    /// @param index The index of a character within the string to be removed. 
    void Remove(size_t index)
    {
        assert(index < length);
        //strcpy(characters + index, characters + index + 1);
        memcpy(characters + index, characters + index + 1, (length - index + 1) * sizeof(char));
        length--;
    }

    /// @brief Inserts a character at the specified index within the dynamic string.
    /// @param index The index of a character to be inserted within the string.
    /// @param character The character to be inserted.
    void Insert(size_t index, char character)
    {
        assert(index < length);

        if (length + 1 > capacity)
            Reallocate(length + 1);
        
        // we use for loop instead of strcpy() to prevent overwriting 
        // by copying characters in the reverse order
        for (size_t i = length; i >= index + 1; i--)
            characters[i] = characters[i-1];
        characters[length + 1] = '\0';

        characters[index] = character;
        length++;
    }

    /// @brief Ensures that the capacity of the dynamic string is at least the 
    /// specified value. If new capacity is greater than the current capacity, 
    /// then the capacity is set to capacity; otherwise the capacity is unchanged.
    /// @param newCapacity New capacity to be assigned.
    /// @return New capacity of the dynamic string.
    size_t Reserve(size_t newCapacity)
    {
        if (capacity < newCapacity)
            Reallocate(newCapacity);

        return capacity;
    }

    /// @brief Sets the dynamic string to the empty string,
    /// clearing all its contents and setting its length to zero 
    /// and capacity to one.
    void Clear()
    {
        // we do not modify the capacity after calling the clear
        SetCharacters("");
    }

    /// @brief Returns a value indicating whether the characters in this instance
    /// are equal to a specified dynamic string.
    /// @param other An object to compare with the dynamic string.
    /// @return true if this instance and the specified string have equal char sequences.
    bool Equals(const DynamicString& other) const
    {
        return Equals(other.characters);
    }

    /// @brief Returns a value indicating whether the characters in this instance 
    /// are equal to the characters in a specified character sequence.
    /// @param otherCharacters A character sequence to compare with the dynamic string.
    /// @return true if this instance and the specified string have equal char sequences.
    bool Equals(const char* otherCharacters) const
    {
        return strcmp(characters, otherCharacters) == 0;
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

    /// @brief Assignment operator that assigns the contents of the 
    /// dynamic string to the new specified character sequence.
    /// Capacity will not change but will increase, if needed.
    /// @param newValue The character sequence to be assigned.
    /// @return A reference to the instance of this dynamic string modified.
    DynamicString& operator=(const char* newValue)
    {
        SetCharacters(newValue);
        return *this;
    }

    /// @brief Copy assignment operator that creates a copy of another 
    /// dynamic string and deletes the previous data of this instance.
    /// @param other The dynamic string to be copied.
    /// @return A reference to the instance of this dynamic string modified.
    DynamicString& operator=(const DynamicString& other)
    {
        if (this != &other)
        {
            delete[] characters;
            DeepCopyFrom(other);
        }

        return *this;
    }

    /// @brief Move assignment operator that moves the data from
    /// another rvalue object of dynamic string to this instance;
    /// @param other A dynamic string rvalue object to be moved.
    /// @return A reference to the instance of this dynamic string modified.
    DynamicString& operator=(DynamicString&& other) noexcept
    {
        if (this != &other)
        {
            delete[] characters;    
            ShallowCopyFrom(std::move(other));
        }

        return *this;
    }

private:
    /// @brief Assings the specified char sequence as the new data 
    /// for the dynamic string. 
    /// @param value The char sequence to be assigned.
    void SetCharacters(const char* value)
    {
        length = strlen(value);
        char* newCharacters = new char[length + 1];
        
        //strcpy(newCharacters, value);
        memcpy(newCharacters, value, (length + 1) * sizeof(char));
        characters = newCharacters;

        capacity = capacity > 0 ? capacity : DEFAULT_CAPACITY;
        capacity = capacity < length ? length : capacity;
    }

    /// @brief Performs a deep copy of the specified dynamic string.
    /// @param other The string to be deep copied.
    void DeepCopyFrom(const DynamicString& other)
    {
        SetCharacters(other.characters);
        length = other.length;
        capacity = other.capacity;
        // for the debug purposes
        std::cout << "Copied!" << std::endl;
    }

    /// @brief Moves all the data from another rvalue object of 
    /// dynamic string to this instance and clears other dynamic string. 
    /// @param other A dynamic string rvalue object to be moved.
    void ShallowCopyFrom(DynamicString&& other)
    {
        // moving just a pointer and not the data itself
        characters = other.characters;
        length = other.length;
        capacity = other.capacity;

        // clearing the original string
        other.characters = nullptr;
        other.length = 0;
        other.capacity = 0;

        // for the debug purposes
        std::cout << "Moved!" << std::endl;
    }

    /// @brief Allocates a new block of memory and moves all 
    /// the existing elements into this new block.
    /// @param newCapacity The capacity of the new block of memory.
    void Reallocate(size_t newCapacity)
    {
        // std::cout << "Reallocating !!!" << std::endl;
        newCapacity = newCapacity > 0 ? newCapacity : DEFAULT_CAPACITY;
        char* newCharacters = new char[newCapacity + 1];
        
        //strcpy(newCharacters, characters);
        memcpy(newCharacters, characters, (length + 1) * sizeof(char));
        delete[] characters;
        
        characters = newCharacters;
        capacity = newCapacity;
    }

#ifdef DEBUG
private:
    inline void PrintBuffer() const
    {
        for (int i = 0; i < capacity; i++)
            std::cout << (characters[i] == 0 ? '.' : characters[i]) << " ";
        std::cout << "(len = " << length << ")" << " (cap = " << capacity << ")" << std::endl;
    }
#endif

private:
    static constexpr size_t DEFAULT_CAPACITY = 1;
    static constexpr size_t GROWTH_FACTOR = 2;

    char* characters = nullptr;
    size_t length = 0;
    size_t capacity = 0;
};