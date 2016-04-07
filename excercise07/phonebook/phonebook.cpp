#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <iterator>

#include "keyname.hpp"
#include "strtool.hpp"
#include "contact.hpp"
#include "contact_manager.hpp"
#include "phonebook.hpp"

#define DELIMITER   '|'
#define MAX_WORD_LENGTH 500

phonebook::phonebook(void) { data = new contact_manager; }
phonebook::~phonebook(void) { delete data; }

int phonebook::load(const std::string path_of_file)
{
    std::ifstream datafile;
    datafile.open(path_of_file);
    if(! datafile.is_open()) return 1;

    for(char line[MAX_WORD_LENGTH]; datafile.getline(&line[0], MAX_WORD_LENGTH); )
    {
        class contact datatemp;

        std::stringstream dataline;
        dataline << strtool::carrtostr(line);

        int key = 0;
        for(char value[MAX_WORD_LENGTH]; dataline.getline(&value[0], MAX_WORD_LENGTH, DELIMITER); )
        {
            datatemp.set(key, strtool::carrtostr(value));
            if(++key >= 8) break;
        }

        data->add(datatemp);
    }
    return 0;
}

void phonebook::prompt(void)
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

        if(cmdtok.size() < 1) continue;
        else if(cmdtok[0] == "exit" || cmdtok[0] == "quit") break;
        else if(cmdtok[0] == "print") data->print();
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
        else if(cmdtok[0] == "sort")
        {
            if(cmdtok.size() < 3)
            {
                std::cout   << "Usage: sort by [type name]" << std::endl
                            << "Available type name:" << std::endl
                            << "   name, company, address, zipcode, phone1, phone2, email, web" << std::endl;
            }
            else
            {
                if(cmdtok[2] == "name") data->sort(NAME);
                else if(cmdtok[2] == "company") data->sort(COMPANY);
                else if(cmdtok[2] == "address") data->sort(ADDRESS);
                else if(cmdtok[2] == "zipcode") data->sort(ZIPCODE);
                else if(cmdtok[2] == "phone1") data->sort(PHONE_PRIMARY);
                else if(cmdtok[2] == "phone2") data->sort(PHONE_SECONDARY);
                else if(cmdtok[2] == "email") data->sort(EMAIL);
                else if(cmdtok[2] == "web") data->sort(WEB);
                else
                {
                    std::cout << "Error: Invalid type name '" << cmdtok[2] << "'." << std::endl;
                    continue;
                }
                std::cout << "Sorted by type name '" << cmdtok[2] << "'."<< std::endl;
            }
        }
        else
        {
            std::cout << "Error: '" << cmdtok[0] << "' command not found." << std::endl;
            continue;
        }
    }
}
