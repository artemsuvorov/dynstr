#include <iostream>
#include <string>

#include "DynamicString.h"

int main()
{
    // DynamicString string = DynamicString("ABC");
    // std::cout << string.Characters() << std::endl;

    DynamicString string;
    string.Add('A');
    string.Add('B');
    string.Add('C');
    string.Add('D');
    // string.Add('A');
    // string.Add('B');
    // string.Add('C');
    // string.Add('C');
    // string[3] = 'F';

    std::cout << string.Characters() << std::endl;

    string.Concatenate("abcd");
    std::cout << string.Characters() << std::endl;

    // std::string str = std::string("sad");
    // str[1] = 'A';
    // std::cout << str << std::endl;
}