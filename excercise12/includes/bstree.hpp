#ifndef __BSTREE_HPP
#define __BSTREE_HPP     1

#include <iostream>
#include <string>
#include <queue>

#include "bstelement.hpp"
#include "bstnode.hpp"

class binary_search_tree
{
private:
    bstnode *root;

    bstnode *new_node(bstelement *element);
    void delete_node(bstnode *node);

    void clear_all_child(bstnode *node);
    bstnode *get_node_by_key(const std::string &key, bstnode *node);
    bstnode *get_tree_minimum(bstnode *x);
    bstnode *get_tree_successor(bstnode *x);

public:
    ~binary_search_tree(void);

    void add(bstelement *element);
    void remove(const std::string &key);
    void find(const std::string &key);
    void traverse_level_order(std::function<void(bstnode *)> what_to_do);
    static void traverse_level_order(bstnode * node, std::function<void(bstnode *)> what_to_do);
    void traverse_in_order(std::function<void(bstnode *)> what_to_do);
    static void traverse_in_order(bstnode * node, std::function<void(bstnode *)> what_to_do);
    void print(bstnode *d);
    void printall(void);
    void printall(bstnode *node);
    bstnode *get_node_by_key(const std::string &key);
    //void sort(const int key); /* Not implemented */
};

binary_search_tree::~binary_search_tree(void)
{
    clear_all_child(root);
}

bstnode *binary_search_tree::new_node(bstelement *element) { return new bstnode(element, NULL); }
void binary_search_tree::delete_node(bstnode *node) { delete node->element; delete node; }

void binary_search_tree::clear_all_child(bstnode *node)
{
    /* Postorder */
    if(node == NULL) return;

    clear_all_child(node->left);
    clear_all_child(node->right);
    delete_node(node);
}

bstnode *binary_search_tree::get_node_by_key(const std::string &key)
{
    return get_node_by_key(key, root);
}

bstnode *binary_search_tree::get_node_by_key(const std::string &key, bstnode *node)
{
    /* Inorder */
    if(node == NULL || key == node->element->key) return node;

    if(key < node->element->key)
        get_node_by_key(key, node->left);
    else
        get_node_by_key(key, node->right);
}

bstnode *binary_search_tree::get_tree_minimum(bstnode *x)
{
    while(x->left != NULL)
        x = x->left;

    return x;
}

bstnode *binary_search_tree::get_tree_successor(bstnode *x)
{
    if(x->right != NULL) return get_tree_minimum(x->right);

    bstnode *y = x->parent;

    while(y != NULL && x == y->right)
    {
        x = y;
        y = y->parent;
    }

    return y;
}

void binary_search_tree::add(bstelement *element)
{
    if(get_node_by_key(element->key, root) != NULL) return; /* Already exists */

    bstnode *newnode = new_node(element);

    bstnode *y = NULL;
    bstnode *x = root;

    while(x != NULL)
    {
        y = x;

        {
            if(newnode->element->key < x->element->key)
                x = x->left;
            else
                x = x->right;
        }
    }

    newnode->parent = y;

    {
        if(y == NULL)
            root = newnode;
        else if(newnode->element->key < y->element->key)
            y->left = newnode;
        else
            y->right = newnode;
    }
}

void binary_search_tree::remove(const std::string &key)
{
    bstnode *t = get_node_by_key(key, root);
    if(t == NULL) return; /* Not exists */

    bstnode *y;
    bstnode *x;
    {
        if(t->left == NULL || t->right == NULL)
            y = t;
        else
            y = get_tree_successor(t);
    }

    {
        if(t->left != NULL)
            x = y->left;
        else
            x = y->right;
    }

    {
        if(x != NULL) x->parent = y->parent;
    }

    {
        if(y->parent == NULL)
            root = x;
        else if(y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    {
        if(y != t) t->element = y->element;
    }

    delete_node(y);
}

void binary_search_tree::traverse_level_order(std::function<void(bstnode *)> what_to_do)
{
    traverse_level_order(root, what_to_do);
}

void binary_search_tree::traverse_level_order(bstnode * node, std::function<void(bstnode *)> what_to_do)
{
    bstnode *n = node;
    std::queue<bstnode *> queue;
    if(n != NULL) queue.push(n);

    while(! queue.empty())
    {
        n = queue.front();
        what_to_do(n);

        queue.pop();
        if(n->left != NULL) queue.push(n->left);
        if(n->right != NULL) queue.push(n->right);
    }
}

void binary_search_tree::traverse_in_order(std::function<void(bstnode *)> what_to_do)
{
    traverse_in_order(root, what_to_do);
}

void binary_search_tree::traverse_in_order(bstnode * node, std::function<void(bstnode *)> what_to_do)
{
    traverse_in_order(node->left, what_to_do);
    what_to_do(node);
    traverse_in_order(node->right, what_to_do);
}

void binary_search_tree::find(const std::string &key)
{
    print(get_node_by_key(key, root));
}

void binary_search_tree::printall(void)
{
    printall(root);
}

void binary_search_tree::printall(bstnode *node)
{
    /* Inorder */
    if(node == NULL) return;

    printall(node->left);
    print(node);
    printall(node->right);
}

void binary_search_tree::print(bstnode *d)
{
    if(d == NULL) return;
    std::cout   << "[" << d->element->key << ":" << d->element->value << "]"
                << " " << d->element->longitude
                << " " << d->element->latitude
                << std::endl;
}

#endif /* !__BSTREE_HPP */
