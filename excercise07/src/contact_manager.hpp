#ifndef __CONTACTMANAGER_HPP
#define __CONTACTMANAGER_HPP     1

#include <string>
#include <vector>

#include "contact.hpp"

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

#endif /* !__CONTACTMANAGER_HPP */
