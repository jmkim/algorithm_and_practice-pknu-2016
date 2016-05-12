#include <iostream>
#include <string>
#include "hash_table.hpp"
#include <time.h>

void randstr(const int length, std::string &out);

int main(void)
{
    srand(time(NULL));

    hash_set<std::string> hs_str(10, 0.8,
        [] (const std::string entry) -> unsigned int
        {
            unsigned int hash = 0;
            for(char c : entry) hash = c + (13 * hash);
            return hash;
        }
    );

    const int s_count = 30;
    std::string arr[s_count];
    for(int i = 0; i < s_count; ++i)
    {
        randstr(10, arr[i]);
        std::cout << arr[i] << std::endl;
    }

    for(std::string s : arr)
    {
        hs_str.add(s);

        std::cout << std::endl;
        hs_str.print();
        std::cout << "count: " << hs_str.size() << std::endl
                  << "capacity: " << hs_str.get_capacity() << std::endl;
    }
}

void randstr(const int length, std::string &out)
{
    char range[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    for (int n = 0; n < length; ++n)
        out.push_back(range[rand() % sizeof(range - 1)]);

    out.push_back('\0');
}
