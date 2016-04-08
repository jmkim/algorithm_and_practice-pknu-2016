#ifndef __PHONEBOOK_HPP
#define __PHONEBOOK_HPP     1

class phonebook
{
private:
    contact_manager *data;
    int load(const std::string path_of_file);

public:
    phonebook(void);
    ~phonebook(void);

    void prompt(void);
};

#endif /* !__PHONEBOOK_HPP */
