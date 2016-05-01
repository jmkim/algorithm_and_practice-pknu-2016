#ifndef __CONTAINER_BINARYSEARCHTREE_HPP
#define __CONTAINER_BINARYSEARCHTREE_HPP    1

#include <functional>

#include "binary_tree.hpp"
#include "binary_search_tree.hpp"

namespace container
{
    template<class ELEMENT> struct node_p : public node<ELEMENT>
    {
        node_p *parent;

        node_p(void) : node<ELEMENT>(), parent(NULL) {}
        node_p(ELEMENT *element) : node<ELEMENT>(element), parent(NULL) {}
        node_p(ELEMENT *element, node_p *parent) : node<ELEMENT>(element), parent(parent) {}
    };

    template<class NODE, class ELEMENT> class binary_search_tree : public binary_tree<NODE, ELEMENT>
    {
    public:
        bool is_empty(void) const;

        NODE *search(const ELEMENT *element);
        void insert(const ELEMENT *element);
        void remove(const ELEMENT *element);

    protected:
        NODE *root;

        binary_search_tree(void) : root(NULL) {}
        ~binary_search_tree(void) { while(! is_empty()) remove(root); }

        NODE *get_minimum(const NODE *node);
        NODE *get_inorder_successor(const NODE *node);
        void insert(const NODE *node);
        void remove(const NODE *node);
    };
}

#include "binary_search_tree.tpp"

#endif /* !__CONTAINER_BINARYSEARCHTREE_HPP */
