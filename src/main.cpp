#include <iostream>
#include <string>
#include <vector>

#include "DynamicString.h"

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

    for (const DynamicString& string : strings)
    {
        std::cout << string << std::endl;
    }
}