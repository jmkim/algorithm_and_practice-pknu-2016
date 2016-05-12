#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <iterator>

#include "../../excercise07/phonebook/keyname.hpp"
#include "../../excercise07/phonebook/strtool.hpp"
#include "../../excercise07/phonebook/contact.hpp"
#include "node.hpp"
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
        contact *datatemp = new contact;

        std::stringstream dataline;
        dataline << strtool::carrtostr(line);

        int key = 0;
        for(char value[MAX_WORD_LENGTH]; dataline.getline(&value[0], MAX_WORD_LENGTH, DELIMITER); )
        {
            datatemp->set(key, strtool::carrtostr(value));
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
        else if(cmdtok[0] == "print") data->printall();
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

                data->find(name);
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

                data->remove(name);
            }
        }
        else
        {
            std::cout << "Error: '" << cmdtok[0] << "' command not found." << std::endl;
            continue;
        }
    }
}
