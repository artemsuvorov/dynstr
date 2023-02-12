#include <iostream>

#include <vector>

#include "DynamicString.h"
#include "DynamicStringComparator.h"

int main()
{
    std::vector<DynamicString> strings;
    strings.reserve(10);

    std::cout << "Enter some strings and press Enter:" << std::endl;
    while (true)
    {
        DynamicString string(16uLL);
        std::cin >> string;

        if (string.Equals("")) break;
        strings.push_back(std::move(string));
    }

    std::sort(strings.begin(), strings.end(),
        DynamicStringComparator::Lexicographical_Reversed_CaseInsensitive);

    std::cout << "Your strings sorted lexicographically in reverse & case insensitive:" << std::endl;
    for (const DynamicString& string : strings)
    {
        std::cout << string << std::endl;
    }
}