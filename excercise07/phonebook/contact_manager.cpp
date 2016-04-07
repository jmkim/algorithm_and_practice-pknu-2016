#include <iostream>
#include <string>
#include <algorithm> /* sort(iter, iter, bool) */
#include <array>
#include <vector>

#include "keyname.hpp"
#include "strtool.hpp"
#include "contact.hpp"
#include "contact_manager.hpp"

void contact_manager::add(const class contact &contact)
{
    data.push_back(contact);
}

void contact_manager::print(void)
{
    for(class contact &d : data)
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

void contact_manager::sort(const int key)
{
    std::sort(data.begin(), data.end(), [=](const class contact &first, const class contact &second)
    {
        if(key == ZIPCODE && strtool::strtoi(first.get(key)) < strtool::strtoi(second.get(key))) return true; /* Sort Zipcode as an integer */
        if(first.get(key).compare(second.get(key)) < 0) return true;
        return false;
    });
}
