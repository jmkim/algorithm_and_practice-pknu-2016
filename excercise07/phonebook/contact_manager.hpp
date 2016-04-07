#ifndef __CONTACTMANAGER_HPP
#define __CONTACTMANAGER_HPP     1

class contact_manager
{
private:
    std::vector<contact> data;

public:
    void add(const contact &contact);
    void print(void);
    void sort(const int key);
};

#endif /* !__CONTACTMANAGER_HPP */
