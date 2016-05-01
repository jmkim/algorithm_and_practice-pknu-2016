#ifndef __BSTELEMENT_HPP
#define __BSTELEMENT_HPP     1

#include <string>

struct bstelement
{
    const std::string key;
    const int value;
    const double longitude;
    const double latitude;

    bstelement(const std::string &city_name, const int &city_code, const double &longitude, const double &latitude) : key(city_name), value(city_code), longitude(longitude), latitude(latitude) {}
};

#endif /* !__BSTELEMENT_HPP */
