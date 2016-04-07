#ifndef __PHONEBOOK_STRTOOL_HPP
#define __PHONEBOOK_STRTOOL_HPP     1

#include <string>
#include <array>

#define MAX_WORD_LENGTH 500

namespace phonebook
{
    struct strtool
    {
        static std::string carrtostr(const std::array<char, MAX_WORD_LENGTH> &src);
        static int strtoi(const std::string &src);
    };
}

#endif /* !__PHONEBOOK_STRTOOL_HPP */
