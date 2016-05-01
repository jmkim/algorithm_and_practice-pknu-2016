#ifndef __BSTNODE_HPP
#define __BSTNODE_HPP   1

#include <string>

#include "bstelement.hpp"

struct bstnode
{
    bstelement *element;
    bstnode *left;
    bstnode *right;
    bstnode *parent;

    bstnode(bstelement *element, bstnode *parent) : element(element), left(NULL), right(NULL), parent(parent) {}
};

#endif /* !__BSTNODE_HPP */
