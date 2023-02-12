#include "DynamicString.h"

// #define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

#ifdef DEBUG
inline void PrintBuffer() const
{
    for (int i = 0; i < capacity; i++)
        std::cout << (characters[i] == 0 ? '.' : characters[i]) << " ";
    std::cout << "(len = " << length << ")" << " (cap = " << capacity << ")" << std::endl;
}
#endif

DynamicString::DynamicString() : DynamicString("") { }

DynamicString::DynamicString(size_t capacity)
{
    Reserve(capacity);
}

DynamicString::DynamicString(const char *value)
{
    SetCharacters(value);
    #ifdef DEBUG
    std::cout << "Created!" << std::endl;
    #endif
}

DynamicString::DynamicString(const DynamicString &other)
{
    DeepCopyFrom(other);
}

DynamicString::DynamicString(DynamicString &&other) noexcept
{
    ShallowCopyFrom(std::move(other));
}

DynamicString::~DynamicString()
{
    delete[] characters;
    #ifdef DEBUG
    std::cout << "Destroyed!" << std::endl;
    #endif
}

void DynamicString::Add(char character)
{
    if (length + 1 > capacity)
        Reallocate(GROWTH_FACTOR * capacity);

    characters[length] = character;
    characters[length + 1] = '\0';
    length++;
}

void DynamicString::Concatenate(const char* value)
{
    if (!value) return;

    size_t valueLength = strlen(value);
    size_t newLength = length + valueLength;
    if (newLength > capacity)
        // Reallocate(newLength + newLength % 2);
        Reallocate(newLength);

    memcpy(characters + length, value, (valueLength + 1) * sizeof(char));
    length = newLength;
}

void DynamicString::Remove(size_t index)
{
    assert(index < length);
    assert(characters != nullptr);

    memcpy(characters + index, characters + index + 1, (length - index + 1) * sizeof(char));
    length--;
}

void DynamicString::Insert(size_t index, char character)
{
    assert(index < length);
    assert(characters != nullptr);

    if (length + 1 > capacity)
        Reallocate(length + 1);
    
    // we use for loop instead of strcpy() to prevent 
    // overwriting by copying characters in reverse order
    for (size_t i = length; i >= index + 1; i--)
        characters[i] = characters[i-1];
    characters[length + 1] = '\0';

    characters[index] = character;
    length++;
}

size_t DynamicString::Reserve(size_t newCapacity)
{
    if (capacity == 0 && newCapacity == 0)
        Reallocate(DEFAULT_CAPACITY);
    else if (capacity < newCapacity)
        Reallocate(newCapacity);

    return capacity;
}

void DynamicString::Clear()
{
    // we do not modify the capacity after calling the clear
    SetCharacters("");
}

bool DynamicString::Equals(const char* otherCharacters) const
{
    return strcmp(characters, otherCharacters) == 0;
}

const char& DynamicString::operator[](size_t index) const
{
    assert(index < length);
    return characters[index];
}

char& DynamicString::operator[](size_t index)
{
    assert(index < length);
    return characters[index];
}

DynamicString& DynamicString::operator=(const char* newValue)
{
    SetCharacters(newValue);
    return *this;
}

DynamicString& DynamicString::operator=(const DynamicString& other)
{
    if (this != &other)
    {
        delete[] characters;
        DeepCopyFrom(other);
    }

    return *this;
}

DynamicString& DynamicString::operator=(DynamicString&& other) noexcept
{
    if (this != &other)
    {
        delete[] characters;    
        ShallowCopyFrom(std::move(other));
    }

    return *this;
}

void DynamicString::SetCharacters(const char* value)
{
    if (!value)
    {
        characters = nullptr;
        length = 0;
        return;
    }

    length = strlen(value);
    char* newCharacters = new char[length + 1];
    
    memcpy(newCharacters, value, (length + 1) * sizeof(char));
    characters = newCharacters;

    capacity = capacity > 0 ? capacity : DEFAULT_CAPACITY;
    capacity = capacity < length ? length : capacity;
}

void DynamicString::DeepCopyFrom(const DynamicString& other)
{
    SetCharacters(other.characters);
    length = other.length;
    capacity = other.capacity;
    #ifdef DEBUG
    std::cout << "Copied!" << std::endl;
    #endif
}

void DynamicString::ShallowCopyFrom(DynamicString&& other)
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
    #ifdef DEBUG
    std::cout << "Moved!" << std::endl;
    #endif
}

void DynamicString::Reallocate(size_t newCapacity)
{
    #ifdef DEBUG
    std::cout << "Reallocating !!!" << std::endl;
    #endif
    if (newCapacity == 0)
        newCapacity = DEFAULT_CAPACITY;

    char* newCharacters = new char[newCapacity + 1];
    
    if (characters)
        memcpy(newCharacters, characters, (length + 1) * sizeof(char));
    else
        // setting a null-terminating character at the start 
        // to create an empty string ""
        newCharacters[0] = '\0';
    delete[] characters;
    
    characters = newCharacters;
    capacity = newCapacity;
}

DynamicString operator+(const DynamicString& string, const char* value)
{
    DynamicString result(string.Length() + strlen(value));
    result.Concatenate(string.Characters());
    result.Concatenate(value);
    return result;
}

DynamicString operator+(const char* value, const DynamicString& string)
{
    DynamicString result(string.Length() + strlen(value));
    result.Concatenate(value);
    result.Concatenate(string.Characters());
    return result;
}

DynamicString operator+(const DynamicString& first, const DynamicString& second)
{
    DynamicString result(first.Length() + second.Length());
    result.Concatenate(first.Characters());
    result.Concatenate(second.Characters());
    return result;
}

std::ostream& operator<<(std::ostream& stream, const DynamicString& string)
{
    const char* characters = string.Characters();
    stream << (characters ? characters : "");
    return stream;
}

std::istream& operator>>(std::istream& stream, DynamicString& string)
{
    char character;
    while (stream.get(character) && !stream.eof())
    {
        if (character == '\n') break;
        string.Add(character);
    }
    return stream;
}