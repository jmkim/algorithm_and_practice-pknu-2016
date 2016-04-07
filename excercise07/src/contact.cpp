#include <string>

#include "contact.hpp"

void phonebook::contact::set(const int key, const std::string value)
{
    data[key] = value;
}

std::string phonebook::contact::get(const int key) const
{
    return data[key];
}
