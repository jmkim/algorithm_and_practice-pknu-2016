#ifndef __STRTOOL_HPP
#define __STRTOOL_HPP     1

#include <string>

struct strtool
{
    static std::string carrtostr(const char carr[]);
    static int strtoi(const std::string &src);
};

#endif /* !__STRTOOL_HPP */
