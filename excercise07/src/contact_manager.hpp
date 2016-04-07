#ifndef __PHONEBOOK_CONTACTMANAGER_HPP
#define __PHONEBOOK_CONTACTMANAGER_HPP     1

#include <string>
#include <vector>

#include "contact.hpp"

namespace phonebook
{
    class contact_manager
    {
    private:
        std::vector<class contact> data;

        int load(const std::string path_of_file);
        void print(void);
        void sort(const int key);

    public:
        void prompt(void);
    };
}

#endif /* !__PHONEBOOK_CONTACTMANAGER_HPP */
