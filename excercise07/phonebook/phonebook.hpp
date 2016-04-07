#ifndef __PHONEBOOK_HPP
#define __PHONEBOOK_HPP     1

class phonebook : public contact_manager
{
private:
    int load(const std::string path_of_file);

public:
    void prompt(void);
};

#endif /* !__PHONEBOOK_HPP */
