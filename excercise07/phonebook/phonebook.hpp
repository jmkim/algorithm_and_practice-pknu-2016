#ifndef __PHONEBOOK_HPP
#define __PHONEBOOK_HPP     1

class phonebook
{
private:
    std::vector<class contact> data;

    int load(const std::string path_of_file);
    void print(void);
    void sort(const int key);

public:
    void prompt(void);
};

#endif /* !__PHONEBOOK_HPP */
