#include <sstream>
#include <string>

#include "strtool.hpp"

std::string strtool::carrtostr(const char carr[])
{
    std::string str;

    for(int i = 0; carr[i] != '\0'; ++i)
        str.push_back(carr[i]);

    return str;
}

int strtool::strtoi(const std::string &src)
{
    int number;

    std::stringstream convert;
    convert << src;
    convert >> number;

    return number;
}
