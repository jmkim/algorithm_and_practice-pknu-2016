#include "element.hpp"

using namespace container;

template<typename D_KEY> bool element<D_KEY>::is_equal(const element *element) const
{
    return key == element->key;
}

template<typename D_KEY> bool element<D_KEY>::is_less_than(const element *element) const
{
    if(key < element->key) return true;
    return false;
}
