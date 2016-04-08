#include <string>
#include <array>

#include "contact.hpp"

void contact::set(const int key, const std::string value)
{
    data[key] = value;
}

std::string contact::get(const int key) const
{
    return data[key];
}
