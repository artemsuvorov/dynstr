#pragma once

#include <assert.h>
#include <cstring>
#include <istream>
#include <ostream>

#include "DynamicStringIterator.h"

/// @brief A dynamic string for managing sequences of characters.
class DynamicString
{
public:
    using Iterator = CharIterator;

public:
    /// @brief Default constructor that creates an empty string.
    DynamicString();

    /// @brief Constructor that creates a dynamic string with the specified capacity.
    /// If capacity is zero, the capacity will be set to the default capacity.
    /// @param capacity The initial capacity of the dynamic string.
    DynamicString(size_t capacity);

    /// @brief Constructor that creates a string consisting of 
    /// the specified characters.
    /// @param value The character sequence to be put in the string.
    DynamicString(const char* value);

    /// @brief A copy constructor that creates a copy of another dynamic string.
    /// @param other The string to be copied.
    DynamicString(const DynamicString& other);

    /// @brief A move constructor that moves an rvalue object of the specified dynamic string.
    /// @param other The string to be moved.
    DynamicString(DynamicString&& other) noexcept;

    /// @brief Destroy the dynamic string instance.
    ~DynamicString();

public:
    /// @brief Adds the specified character at the end of 
    /// the string before the null-terminating character.
    /// @param character The character to be added to the string.
    void Add(char character);

    /// @brief Concatenates the specified string to the dynamic string.
    /// @param value The string to be concatenated.
    void Concatenate(const char* value);

    /// @brief Removes a character from the dynamic string at the specified index.
    /// @param index The index of a character within the string to be removed. 
    void Remove(size_t index);

    /// @brief Inserts a character at the specified index within the dynamic string.
    /// @param index The index of a character to be inserted within the string.
    /// @param character The character to be inserted.
    void Insert(size_t index, char character);

    /// @brief Ensures that the capacity of the dynamic string is at least the 
    /// specified value. If new capacity is greater than the current capacity, 
    /// then the capacity is set to capacity; otherwise the capacity is unchanged.
    /// @param newCapacity New capacity to be assigned.
    /// @return New capacity of the dynamic string.
    size_t Reserve(size_t newCapacity);

    /// @brief Sets the dynamic string to the empty string,
    /// clearing all its contents and setting its length to zero 
    /// and capacity to one.
    void Clear();

    /// @brief Returns a value indicating whether the characters in this instance
    /// are equal to a specified dynamic string.
    /// @param other An object to compare with the dynamic string.
    /// @return true if this instance and the specified string have equal char sequences.
    bool Equals(const DynamicString& other) const { return Equals(other.characters); }

    /// @brief Returns a value indicating whether the characters in this instance 
    /// are equal to the characters in a specified character sequence.
    /// @param otherCharacters A character sequence to compare with the dynamic string.
    /// @return true if this instance and the specified string have equal char sequences.
    bool Equals(const char* otherCharacters) const;

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

    /// @brief Returns a read/write iterator that points to the first
    /// character in the dynamic string.
    /// @return A read/write iterator that points to the first
    /// character in the dynamic string.
    Iterator begin() const { return Iterator(characters); }

    /// @brief Returns a read/write iterator that points one past the
    /// last character in the dynamic string.
    /// @return A read/write iterator that points one past the
    /// last character in the dynamic string.
    Iterator end() const { return Iterator(characters + length); }

public:
    /// @brief Returns a character of a string at the specified index.
    /// @param index The index within the string at which the character will be returned. 
    /// @return Character of a string at the specified index.
    const char& operator[](size_t index) const;

    /// @brief Returns a character of a string at the specified index.
    /// @param index The index within the string at which the character will be returned. 
    /// @return Character of a string at the specified index.
    char& operator[](size_t index);

    /// @brief Assignment operator that assigns the contents of the 
    /// dynamic string to the new specified character sequence.
    /// Capacity will not change but will increase, if needed.
    /// @param newValue The character sequence to be assigned.
    /// @return A reference to the instance of this dynamic string modified.
    DynamicString& operator=(const char* newValue);

    /// @brief Copy assignment operator that creates a copy of another 
    /// dynamic string and deletes the previous data of this instance.
    /// @param other The dynamic string to be copied.
    /// @return A reference to the instance of this dynamic string modified.
    DynamicString& operator=(const DynamicString& other);

    /// @brief Move assignment operator that moves the data from
    /// another rvalue object of dynamic string to this instance;
    /// @param other A dynamic string rvalue object to be moved.
    /// @return A reference to the instance of this dynamic string modified.
    DynamicString& operator=(DynamicString&& other) noexcept;

    /// @brief Equality operator to check if this instance of dynamic string
    /// equals to another dynamic string.
    /// @param other The other dynamic string to be compared with this instance.
    /// @return True if strings equal, otherwise false.
    bool operator==(const DynamicString& other) const;

    /// @brief Inequality operator to check if this instance of dynamic string
    /// does not equal to another dynamic string.
    /// @param other The other dynamic string to be compared with this instance.
    /// @return True if strings do not equal, otherwise false.
    bool operator!=(const DynamicString& other) const { return !(*this == other); }

private:
    /// @brief Assings the specified char sequence as the new data 
    /// for the dynamic string. 
    /// @param value The char sequence to be assigned.
    void SetCharacters(const char* value);

    /// @brief Performs a deep copy of the specified dynamic string.
    /// @param other The string to be deep copied.
    void DeepCopyFrom(const DynamicString& other);

    /// @brief Moves all the data from another rvalue object of 
    /// dynamic string to this instance and clears other dynamic string. 
    /// @param other A dynamic string rvalue object to be moved.
    void ShallowCopyFrom(DynamicString&& other);

    /// @brief Allocates a new block of memory and moves all 
    /// the existing elements into this new block.
    /// @param newCapacity The capacity of the new block of memory.
    void Reallocate(size_t newCapacity);

private:
    static constexpr size_t DEFAULT_CAPACITY = 1;
    static constexpr size_t GROWTH_FACTOR = 2;

    char* characters = nullptr;
    size_t length = 0;
    size_t capacity = 0;
};

// Plus operator outside of the main class

/// @brief Plus operator that concatenates dynamic string and a C-string 
/// and returns the result.
/// @param string The dynamic string to be concatenated.
/// @param value The C-string to be concatenated.
/// @return The result of concatenation of two strings.
DynamicString operator+(const DynamicString& string, const char* value);

/// @brief Plus operator that concatenates C-string and a dynamic string 
/// and returns the result.
/// @param string The dynamic string to be concatenated.
/// @param value The C-string to be concatenated.
/// @return The result of concatenation of two strings.
DynamicString operator+(const char* value, const DynamicString& string);

/// @brief Plus operator that concatenates two strings and returns the result.
/// @param first The first string to be concatenated.
/// @param second The second string to be concatenated.
/// @return The result of concatenation of two strings.
DynamicString operator+(const DynamicString& first, const DynamicString& second);

/// @brief Pushes dynamic string to the output stream. 
/// @param stream The output stream to accept the string.
/// @param string The dynamic string to be pushed to the output stream.
/// @return The output stream containing the dynamic string.
std::ostream& operator<<(std::ostream& stream, const DynamicString& string);

/// @brief From an input stream reads the string char by char 
/// while can or new-line character is not found.
/// @param stream The input stream to read from.
/// @param string The string to be assigned to the read value.
/// @return The input stream.
std::istream& operator>>(std::istream& stream, DynamicString& string);