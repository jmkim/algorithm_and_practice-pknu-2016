#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include <iterator>

#include "strtool.hpp"
#include "contact.hpp"
#include "contact_manager.hpp"

#define DELIMITER   '|'
#define MAX_WORD_LENGTH 500

#define NAME        0
#define COMPANY     1
#define ADDRESS     2
#define ZIPCODE     3
#define PHONE_PRIMARY   4
#define PHONE_SECONDARY 5
#define EMAIL       6
#define WEB         7

int contact_manager::load(const std::string path_of_file)
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

        data.push_back(datatemp);
    }
    return 0;
}

void contact_manager::print(void)
{
    for(class contact &d : data)
    {
        std::cout   << d.get(NAME) << std::endl
                    << "\tCompany: " << d.get(COMPANY) << std::endl
                    << "\tAddress: " << d.get(ADDRESS) << std::endl
                    << "\tZipcode: " << d.get(ZIPCODE) << std::endl
                    << "\tPhones:  " << d.get(PHONE_PRIMARY) << ", " << d.get(PHONE_SECONDARY) << std::endl
                    << "\tEmail:   " << d.get(EMAIL) << std::endl
                    << "\tWeb:     " << d.get(WEB) << std::endl
                    << std::endl;
    }
}

void contact_manager::sort(const int key)
{
    std::sort(data.begin(), data.end(), [=](const class contact &first, const class contact &second)
    {
        if(key == ZIPCODE && strtool::strtoi(first.get(key)) < strtool::strtoi(second.get(key))) return true; /* Sort Zipcode as an integer */
        if(first.get(key).compare(second.get(key)) < 0) return true;
        return false;
    });
}

void contact_manager::prompt(void)
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
        else if(cmdtok[0] == "print") print();
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
                if(cmdtok[2] == "name") sort(NAME);
                else if(cmdtok[2] == "company") sort(COMPANY);
                else if(cmdtok[2] == "address") sort(ADDRESS);
                else if(cmdtok[2] == "zipcode") sort(ZIPCODE);
                else if(cmdtok[2] == "phone1") sort(PHONE_PRIMARY);
                else if(cmdtok[2] == "phone2") sort(PHONE_SECONDARY);
                else if(cmdtok[2] == "email") sort(EMAIL);
                else if(cmdtok[2] == "web") sort(WEB);
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
