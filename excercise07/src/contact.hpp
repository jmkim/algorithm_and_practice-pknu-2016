#ifndef __PHONEBOOK_CONTACT_HPP
#define __PHONEBOOK_CONTACT_HPP     1

#include <string>
#include <array>

namespace phonebook
{
    class contact
    {
    private:
        std::array<std::string, 8> data;

    public:
        void set(const int key, const std::string value);
        std::string get(const int key) const;
    };
}

#endif /* !__PHONEBOOK_CONTACT_HPP */
