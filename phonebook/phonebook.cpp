#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>

#include "parser.cpp"
#include "contactmanager.cpp"

class phonebook
{
private:
    contactmanager pb_data;
    void print(const std::string contact[][2], const int size_of_array)
    {
#if 0
    void print(const std::string contact[][2])
    {
        for(std::string c[2] : contact)
        {
            if(c[0] == "Name" || c[0] == "name")
                std::cout << c[1] << std::endl;
            else
                std::cout << "\t" << c[0] << "\t" << c[1] << std::endl;
        }
#endif
        for(int i = 0; i < size_of_array; ++i)
        {
            if(contact[i][0] == "Name" || contact[i][0] == "name")
                std::cout << contact[i][1] << std::endl;
            else
                std::cout << "\t" << contact[i][0] << "\t" << contact[i][1] << std::endl;
        }
    }

    int load(const std::string &path_of_file)
    {
        parser fp(path_of_file);
        fp.parse(
            [&] (const std::string &line)
            {
                std::string key[] =
                {
                    "Name",
                    "Company",
                    "Address",
                    "Zipcode",
                    "Phone",
                    "Phone (secondary)",
                    "Email",
                    "Web"
                };
                std::string value[8];
                int count_of_value = fp.divide_by_delimiter(value, line, 8, '|');

                std::string contact[8][2];
                for(int i = 0; i < 8; ++i)
                {
                    contact[i][0] = key[i];
                    contact[i][1] = value[i];
                }

                pb_data.add(contact, 8);
            }
        );
        fp.close();
    }

public:
    int prompt(void)
    {
        while(true)
        {
            std::string cmdline;
            std::cout << "$ "; std::getline(std::cin, cmdline);

            std::istringstream cmd(cmdline);
            std::vector<std::string> cmdtok =
            {
                std::istream_iterator<std::string>{cmd},
                std::istream_iterator<std::string>{}
            };

            if(cmdtok.size() < 1) continue; /* Just press CR */
            else if(cmdtok[0] == "exit" || cmdtok[0] == "quit") break;
            else if(cmdtok[0] == "print")
            {
                std::string contacts[9000][15][2];
                pb_data.lookup_inorder(contacts, 9000);

                for(std::string contact[15][2] : contacts) print(contact, 15);
            }
            else if(cmdtok[0] == "read")
            {
                if(cmdtok.size() < 2)
                    std::cout << "Usage: read [file name]" << std::endl;
                else
                {
                    switch(load(cmdtok[1]))
                    {
                        case 0: std::cout << "File " << cmdtok[1] << " loaded." << std::endl; break;
                        case 1: std::cout << "Error: File " << cmdtok[1] << " not found." << std::endl; break;
                    }
                }
            }
            else if(cmdtok[0] == "find")
            {
                if(cmdtok.size() < 2)
                    std::cout << "Usage: find [name]" << std::endl;
                else
                {
                    std::string name;
                    int i;

                    for(i = 1; i < cmdtok.size() - 1; ++i)
                        name += cmdtok[i] + " ";
                    name += cmdtok[i];

                    std::cout << "'" << name << "'" << std::endl;

                    std::string contact[15][2];
                    pb_data.lookup(name, contact, 15);

                    print(contact, 15);
                }
            }
            else if(cmdtok[0] == "delete")
            {
                if(cmdtok.size() < 2)
                    std::cout << "Usage: delete [name]" << std::endl;
                else
                {
                    std::string name;
                    int i;

                    for(i = 1; i < cmdtok.size() - 1; ++i)
                        name += cmdtok[i] + " ";
                    name += cmdtok[i];

                    std::cout << "'" << name << "'" << std::endl;

                    pb_data.remove(name);
                }
            }
            else
            {
                std::cout << "Error: '" << cmdtok[0] << "' command not found." << std::endl;
                continue;
            }
        }

        pb_data.remove_postorder();
        std::cout << "Exiting.." << std::endl;
    }
};
