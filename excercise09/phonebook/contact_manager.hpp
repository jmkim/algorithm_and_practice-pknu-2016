#ifndef __CONTACTMANAGER_HPP
#define __CONTACTMANAGER_HPP     1

class contact_manager
{
private:
    node *data;

public:
    void add(const contact &contact);
    void remove(const std::string &name);
    void print(void);
    //void sort(const int key); /* Not implemented */
};

#endif /* !__CONTACTMANAGER_HPP */
