#ifndef __PHONEBOOK_STRTOOL_HPP
#define __PHONEBOOK_STRTOOL_HPP     1

#include <string>

namespace phonebook
{
    struct strtool
    {
        static std::string carrtostr(const char carr[]);
        static int strtoi(const std::string &src);
    };
}

#endif /* !__PHONEBOOK_STRTOOL_HPP */
