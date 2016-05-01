#ifndef __CONTAINER_ELEMENT_HPP
#define __CONTAINER_ELEMENT_HPP     1

namespace container
{
    template<typename D_KEY> class element
    {
    private:
        const D_KEY key;

    public:
        element(const D_KEY &key) : key(key) {}

        bool is_equal(const element *element) const;
        bool is_less_than(const element *element) const; /* Return true if `me' is less than `element' */
    };
}

#include "element.tpp"

#endif /* !__CONTAINER_ELEMENT_HPP */
