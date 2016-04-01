#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <array>
#include <vector>
#include <iterator>

#define MAX_WORD_LENGTH 500
#define DELIMITER   '|'

namespace excercise07
{
    enum keyname : int { name, company, address, zipcode, phone1, phone2, email, web };

    struct strtool
    {
        static std::string carytostr(const std::array<char, MAX_WORD_LENGTH> &src)
        {
            std::string str;
            for(char c : src)
            {
                if(c == '\0') break;
                str.push_back(c);
            }

            return str;
        }

        static int strtoi(const std::string &src)
        {
            int number;

            std::stringstream convert;
            convert << src;
            convert >> number;

            return number;
        }
    };

    class contact
    {
    private:
        std::array<std::string, 8> data;

    public:
        void set(const int key, const std::string value) { data[key] = value; }
        void set(const enum keyname key, const std::string value) { data[key] = value; }

        std::string get(const int key) const { return data[key]; }
        std::string get(const enum keyname key) const { return data[key]; }
    };

    class contact_manager
    {
    private:
        std::vector<class contact> data;

        int load(const std::string path_of_file)
        {
            std::ifstream datafile;
            datafile.open(path_of_file);
            if(! datafile.is_open()) return 1;

            for(std::array<char, MAX_WORD_LENGTH> line; datafile.getline(&line[0], MAX_WORD_LENGTH); )
            {
                class contact datatemp;

                std::stringstream dataline;
                dataline << strtool::carytostr(line);
    
                int key = 0;
                for(std::array<char, MAX_WORD_LENGTH> value; dataline.getline(&value[0], MAX_WORD_LENGTH, DELIMITER); )
                {
                    datatemp.set(key, strtool::carytostr(value));
                    if(++key >= 8) break;
                }

                data.push_back(datatemp);
            }
            return 0;
        }
        void print(void)
        {
            for(class contact &d : data)
            {
                std::cout   << d.get(name) << std::endl
                            << "\tCompany: " << d.get(company) << std::endl
                            << "\tAddress: " << d.get(address) << std::endl
                            << "\tZipcode: " << d.get(zipcode) << std::endl
                            << "\tPhones:  " << d.get(phone1) << ", " << d.get(phone2) << std::endl
                            << "\tEmail:   " << d.get(email) << std::endl
                            << "\tWeb:     " << d.get(web) << std::endl
                            << std::endl;
            }
        }

        void sort(const enum keyname key)
        {
            std::sort(data.begin(), data.end(), [=](const class contact &first, const class contact &second)
            {
                if(key == zipcode && strtool::strtoi(first.get(key)) < strtool::strtoi(second.get(key))) return true; /* Sort Zipcode as an integer */
                if(first.get(key).compare(second.get(key)) < 0) return true;
                return false;
            });
        }

    public:
        void prompt(void)
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

                if(cmdtok[0] == "read")
                if(cmdtok.size() < 1) continue;
                {
                    if(cmdtok.size() < 2)
                        std::cout << "Usage: read [file name]" << std::endl;
                    else
                        switch(load(cmdtok[1]))
                        {
                            case 0: std::cout << "File " << cmdtok[1] << " loaded." << std::endl; break;
                            case 1: std::cout << "Error: File " << cmdtok[1] << " not found." << std::endl; break;
                        }
                }
                else if(cmdtok[0] == "print")
                    print();
                else if(cmdtok[0] == "sort")
                {
                    if(cmdtok.size() < 3)
                    {
                        std::cout   << "Usage: sort as [sort-key]" << std::endl
                                    << "Available sort-key:" << std::endl
                                    << "   name, company, address, zipcode, phone1, phone2, email, web" << std::endl;
                    }
                    else
                    {
                        if(cmdtok[2] == "name")
                            sort(name);
                        else if(cmdtok[2] == "company")
                            sort(company);
                        else if(cmdtok[2] == "address")
                            sort(address);
                        else if(cmdtok[2] == "zipcode")
                            sort(zipcode);
                        else if(cmdtok[2] == "phone1")
                            sort(phone1);
                        else if(cmdtok[2] == "phone2")
                            sort(phone2);
                        else if(cmdtok[2] == "email")
                            sort(email);
                        else if(cmdtok[2] == "web")
                            sort(web);
                        else
                        {
                            std::cout << "sort-key not found" << std::endl;
                            continue;
                        }
                        std::cout << "Sorted with sort-key " << cmdtok[2] << std::endl;
                    }
                }
                else if(cmdtok[0] == "exit" || cmdtok[0] == "quit")
                    break;
                else
                    std::cout << "" << std::endl;
            }
        }
    };
}

int main(void)
{
    excercise07::contact_manager cm;
    cm.prompt();

    return 0;
}
