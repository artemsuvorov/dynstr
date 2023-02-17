# Dynamic Strings

dynstr is a small project containing an implementation of a class of dynamic strings that consist of single-byte ASCII characters and support concatenation, insertion, modification, and deletion of substrings or single characters.

Dynamic strings are mutable strings represented by a one-dimensional `char` array located on the heap. For a string, the memory allocation process is encapsulated within the dynamic string class: it automatically allocates and deallocates memory blocks as needed. 

The dynamic string class itself is written in the C++11 standart, although the project also contains tests written using the [`googletest`](https://github.com/google/googletest) library, which requires C++14. Via `CMake` utility, the program and tests can be compiled into executable files using the required version of C++.

## Restrictions

Dynamic strings class has the following features:

1. It is written in C++11 without any third party libraries. Does not rely on any other implementation of dynamic strings, containers, or STL smart pointers at its core.
2. Class is non-generic and doesn't use templates. Supports strings of arbitrary size using basic dynamic heap operations (`malloc()` and `free()` functions or `new` and `delete` opeartors) to manipulate sequences of `char` characters.
3. Class has a copy constructor, an assignment operator, and supports move semantics. 

The dynamic strings class has a plus operator for adding (i.e. concatenating) two strings implemented outside of the main body of the class.

The implementation on itself does not contain any sophisticated optimization methods (such as COW and multi-thread support).

The example program in the main function is written using this dynamic string class and an STL container. The program takes a list of strings, then prints it out in reverse lexicographic order, case insensitive. The program works from the command line.

## Implementation

Internally, the dynamic string class is a regular array of `char` characters of length `length` and capacity `capacity` associated with it. Basically, `length` is a length of the string, i.e. the number of characters it contains that come before the null-terminating character of `'\0'`, while the `capacity` describes the number of characters that can be inserted into the string before a new block of memory needs to be reallocated for a new array of `char` characters.

For example, if an initially empty string has a capacity of 3, then exactly 3 characters could be fit into it. Adding the 4th character using the `Add('...')` method will entail the reallocation of a new block of memory 2 times longer, into which all the characters of the string will be copied and a new 4th one will be added to. At the same time, when calling `Concatenate("...")`, the capacity grows exactly by as many characters as the additional string length (if the length of the latter is greater than the current capacity).

### Properties

| Type        | Property     | Description   |
|:------------|:-------------|:-----------|
| `const char*` | `Characters()` | Returns the sequence of characters that the dynamic string contains |
| `uint32_t`    | `Length()` | Returns the length of the dynamic string |
| `uint32_t`    | `Capacity()` | Returns the capacity of the dynamic string |

### Methods

| Method signature | Description |
|:-----------------|:---------|
| `void Add(char character)` | Add one specified character to the end of the dynamic string |
| `void Concatenate(const char* value)` | Add the specified sequence of characters to the end of the dynamic string |
| `void Insert(size_t index, char character)` | Inserts one character at the specified position within the dynamic string |
| `void Remove(size_t index)` | Removes one character at the specified position within the dynamic string |
| `size_t Reserve(size_t newCapacity)` | Sets the new capacity in characters for the dynamic string to accommodate |
| `void Clear()` | Clears a dynamic string, making it empty |
| `bool Equals(const DynamicString& other)` | Checks if the dynamic string is equal to another one. This method also has an overload for `const char*` value |

### Example

The following example illustrates the use of dynamic strings using the container `vector` from the STL library:

```cpp
int main()
{
    std::vector<DynamicString> strings;
    strings.reserve(10);

    while (true)
    {
        DynamicString string(16uLL);
        std::cin >> string;
        if (string.Equals("")) break;
        strings.push_back(std::move(string));
    }

    std::sort(strings.begin(), strings.end(),
        DynamicStringComparator::Lexicographical_Reversed_CaseInsensitive);

    for (const DynamicString& string : strings)
        std::cout << string << std::endl;
}
```

In this example, we sequentially read lines from the input stream and add them to the `strings` list until we encounter an empty string. In this case, no copying of string objects occurs, since the class supports move semantics. After that, we sort the resulting list using the implemented iterator for dynamic strings in reverse lexicographic order, case insensitive.

Thus, for a given set of lines entered in the terminal:

```sh
{ "a", "B", "c", "D" }
```

the program will print them in the following output order:

```sh
{ "D", "c", "B", "a" }
```

## Quick Start

Make sure the project repository has been cloned with the `--recursive` flag to additionally clone the `googletest` library added to the project as a submodule. The implementation of the dynamic string class itself does not depend on any libraries, therefore, generally speaking, it can be compiled separately. The project can be built and compiled into an executable file using `CMake`. For Windows, the `MinGW` development tool may also be required.

### Unix
```sh
cmake -S . -B build
make -C build
``` 

### Windows
```sh
# On windows:
cmake -S . -B build -G "MinGW Makefiles"
mingw32-make -C build
``` 

Аfter that, the `bin/` directory will contain two executable files for the compiled program itself and the runnable tests:

```tree
bin/
|-- dynstr.exe       # Example program
`-- test-dynstr.exe  # Tests
```

## Tests

The project also contains tests written via the [`googletest`](https://github.com/google/googletest) library. All necessary dependencies are included when building with `CMake`.

### Example

The unit tests written in the project simultaneously provide up-to-date documentation for the dynamic string class. For instance, in one of the tests, the following requirements are declared for an empty string that can be instantiated using the parameter-less constructor:

1. The underlying array of characters is equal to an empty string literal `""`;
2. The dynamic string length is `0`;
3. The default dynamic string capacity is `1` (see Implementation for more details on the capacity).

```cpp
#include <gtest/gtest.h>
#include "DynamicString.h"

TEST(DynstrTest, IsEmptyOnInit)
{
    DynamicString string;

    EXPECT_STREQ(string.Characters(), "");
    EXPECT_EQ(string.Length(), 0);
    EXPECT_EQ(string.Capacity(), 1);
}
```

The next unit test example checks that the dynamic string can dynamically allocate memory for itself by increasing its capacity.

First, an empty dynamic string of length `0` is created and its current capacity is stored to a variable (by default it is `1`, as required by the unit test above). Then two characters are sequentially added to the string: with a capacity equal to one, the first one fits into it, while the second will require a new memory block (2 times larger than the previous one) to be allocated. Thus, the test expects to receive a new capacity that would be greater than the original one and equal to `2`.

```cpp
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
```

### Launch

To run all unit tests from the `test` directory, just compile the program and execute the `test-dynstr.exe` file:

```sh
./bin/test-dynstr.exe
```