#ifndef __CONTACT_HPP
#define __CONTACT_HPP     1

class contact
{
private:
    std::array<std::string, 8> data;

public:
    void set(const int key, const std::string value);
    std::string get(const int key) const;
};

#endif /* !__CONTACT_HPP */
