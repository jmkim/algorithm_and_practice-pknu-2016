#include <iostream>
#include <string>
#include "hash_table.cpp"
#include <time.h>

void randstr(const int length, std::string &out)
{
    char range[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    for (int n = 0; n < length; ++n)
        out.push_back(range[rand() % sizeof(range - 1)]);

    out.push_back('\0');
}

int main(void)
{
    srand(time(NULL));

    hash_set<std::string> hs_str(10, 0.8,
        [] (const std::string entry) -> int
        {
            int hash = 0;
            for(char c : entry) hash = c + (13 * hash);
            return hash;
        }
    );

    std::function<void(int, std::string)> pr_str =
        [](const int table_key, const std::string entry)
        {
#if 0
            static int last_key = -1;
            if(last_key != table_key)
            {
#endif
                std::cout << std::endl << "[" << table_key << "] ";
#if 0
                last_key = table_key;
            }
#endif
            std::cout << entry;
        };

    const int s_count = 30;
    std::string arr[s_count];
    for(int i = 0; i < s_count; ++i) randstr(10, arr[i]);

    for(std::string s : arr)
    {
        hs_str.add(s);

        hs_str.print(pr_str);
        std::cout << std::endl
                    << "count: " << hs_str.size() << std::endl
                    << "capacity: " << hs_str.get_capacity() << std::endl;
    }
}

void run(const int num)
{
    std::cout << num << std::endl;
}
