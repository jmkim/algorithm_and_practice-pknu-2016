#ifndef __CONTAINER_ELEMENT_HPP
#define __CONTAINER_ELEMENT_HPP     1

namespace container
{
    template<typename D_KEY> class element
    {
    public:
        virtual bool is_equal(const element &element) = 0;
        virtual bool is_less_than(const element &element) = 0;  /* Return true if `me' is less than `element' */
    };
}

#endif /* !__CONTAINER_ELEMENT_HPP */
