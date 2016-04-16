#include <functional>

#include "binary_tree.hpp"
#include "binary_search_tree.hpp"

using namespace container;

template<class NODE, class ELEMENT> bool binary_search_tree<NODE, ELEMENT>::is_empty(void) const { return root == NULL; }

template<class NODE, class ELEMENT> NODE *binary_search_tree<NODE, ELEMENT>::search(const ELEMENT *element)
{
    NODE *n = NULL;
    traverse_inorder(root, [&] (NODE *node) { if(node->element->is_equal(element)) n = node; });

    return n;
}

template<class NODE, class ELEMENT> void binary_search_tree<NODE, ELEMENT>::insert(const ELEMENT *element) { insert(create_node(element)); }

template<class NODE, class ELEMENT> void binary_search_tree<NODE, ELEMENT>::remove(const ELEMENT *element)
{
    NODE *node = search(element);
    remove(node);
    destroy_node(node);
}

template<class NODE, class ELEMENT> NODE *binary_search_tree<NODE, ELEMENT>::get_minimum(const NODE *node)
{
    while(node->left != NULL) node = node->left;
    return node;
}

template<class NODE, class ELEMENT> NODE *binary_search_tree<NODE, ELEMENT>::get_inorder_successor(const NODE *node)
{
    /* Downward */
    if(node->right != NULL) return get_minimum(node->right);

    /* Upward */
    NODE *n = node;
    NODE *p = node->parent;

    while(p != NULL && n == p->right)
    {
        n = p;
        p = p->parent;
    }

    return p;
}

template<class NODE, class ELEMENT> void binary_search_tree<NODE, ELEMENT>::insert(const NODE *node)
{
    if(is_empty())
    {
        root = node;
        return;
    }

    NODE *n = root;
    NODE *p = NULL; /* One step previous node of n */

    while(n != NULL)
    {
        p = n;

        if(node->element->is_less_than(n->element))
            n = n->left;
        else
            n = n->right;
    }

    if(node->element->is_less_than(p->element))
        p->left = node;
    else
        p->right = node;

    node->parent = p;
}

template<class NODE, class ELEMENT> void binary_search_tree<NODE, ELEMENT>::remove(const NODE *node)
{
    if(node == NULL) return; /* Not exists */

    if(node->left != NULL && node->right != NULL)
    {
        NODE *s = get_inorder_successor(node);
        if(s->parent != NULL) s->parent->right = s->right;

        if(node->parent == NULL)
            root = s;
        else
        {
            if(node->parent->left == node)
                node->parent->left = s;
            else
                node->parent->right = s;
        }

        s->left = node->left;
        s->right = node->right;
        s->parent = node->parent;
    }
    else
    {
        if(node->parent == NULL)
            root = NULL;
        else
        {
            if(node->parent->left == node)
                node->parent->left = node->left;
            else
                node->parent->right = node->right;
        }
    }
}
