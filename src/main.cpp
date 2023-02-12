#include <iostream>
#include <string>

#include <vector>

#include "DynamicString.h"

// std::ostream& operator <<(std::ostream& stream, const DynamicString& string)
// {
//     const char* characters = string.Characters();
//     stream << (characters ? characters : "");
//     return stream;
// }

// struct Person {
//     const DynamicString Name;
//     Person(const DynamicString& name) : Name(name) {}
//     Person(DynamicString&& name) : Name(std::move(name)) {}
//     void PrintName() const { std::cout << Name << std::endl; }
// };

int main()
{
    // DynamicString a = "asd", b;
    // b = "!hi";
    // DynamicString c = a + b;
    // std::cout << c << std::endl;

    // Move sematics test

    // Person person("Bob");
    // person.PrintName();

    // DynamicString apple = "Apple";
    // DynamicString banana = "Banana";

    // std::cout << "Apple: '" << apple << "'" << std::endl;
    // std::cout << "Banana: '" << banana << "'" << std::endl;

    // banana = std::move(apple);
    // std::cout << "Apple: '" << apple << "'" << std::endl;
    // std::cout << "Banana: '" << banana << "'" << std::endl;

    // DynamicString first = "Hello";
    // DynamicString second = first;

    // first[1] = 'a';

    // std::cout << first << std::endl;
    // std::cout << second << std::endl;

    // DynamicString string = "ABCD";
    // string.Insert(0, '_');
    // string.Remove(2);
    // std::cout << string << std::endl;

    // std::vector<DynamicString> strings;
    // strings.emplace_back("Hello!");
    // strings.emplace_back("Hello 2!");
    // for (const DynamicString& string : strings)
    //     std::cout << string << std::endl;

    // DynamicString string = DynamicString("ABC");
    // std::cout << string.Characters() << std::endl;

    // DynamicString string;
    // string.Add('A');
    // string.Add('B');
    // string.Add('C');
    // string.Add('D');
    // string.Add('A');
    // string.Add('B');
    // string.Add('C');
    // string.Add('C');
    // string[3] = 'F';

    // std::cout << string.Characters() << std::endl;

    // string.Concatenate("abcd");
    // std::cout << string.Characters() << std::endl;

    // std::string str = std::string("sad");
    // str[1] = 'A';
    // std::cout << str << std::endl;
}