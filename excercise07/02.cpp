#include <string>
#include <array>
#include <vector>

#include "phonebook/contact.hpp"
#include "phonebook/contact_manager.hpp"

int main(void)
{
    contact_manager contacts;
    contacts.prompt();

    return 0;
}
