#include <iostream>
#include <string>
#include <algorithm> /* sort(iter, iter, bool) */
#include <array>
#include <vector>

#include "../../excercise07/phonebook/keyname.hpp"
#include "../../excercise07/phonebook/strtool.hpp"
#include "../../excercise07/phonebook/contact.hpp"
#include "contact_manager.hpp"

void contact_manager::add(const contact &contact)
{
    /* TODO: Add a binary tree add */
    //data.push_back(contact);
}

void contact_manager::remove(const std::string &name)
{
    /* TODO: Add a binary tree remove */
}

void find(const std::string &name)
{
    /* TODO: Add a function search */
}

void contact_manager::print(void)
{
    for(contact &d : data)
    {
        std::cout   << d.get(NAME) << std::endl
                    << "\tCompany: " << d.get(COMPANY) << std::endl
                    << "\tAddress: " << d.get(ADDRESS) << std::endl
                    << "\tZipcode: " << d.get(ZIPCODE) << std::endl
                    << "\tPhones:  " << d.get(PHONE_PRIMARY) << ", " << d.get(PHONE_SECONDARY) << std::endl
                    << "\tEmail:   " << d.get(EMAIL) << std::endl
                    << "\tWeb:     " << d.get(WEB) << std::endl
                    << std::endl;
    }
}
