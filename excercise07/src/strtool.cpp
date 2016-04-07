#include <sstream>
#include <string>
#include <array>

#include "strtool.hpp"

std::string phonebook::strtool::carrtostr(const std::array<char, MAX_WORD_LENGTH> &src)
{
    std::string str;
    for(char c : src)
    {
        if(c == '\0') break;
        str.push_back(c);
    }

    return str;
}

int phonebook::strtool::strtoi(const std::string &src)
{
    int number;

    std::stringstream convert;
    convert << src;
    convert >> number;

    return number;
}
