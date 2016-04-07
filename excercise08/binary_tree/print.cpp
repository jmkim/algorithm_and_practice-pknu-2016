#include <iostream>
#include <queue>

#include "node.hpp"
#include "print.hpp"

void binary_tree::print::inorder(node *n)
{
    if(n == NULL) return;

    inorder(n->get_left());
    std::cout << n->get_data() << std::endl;
    inorder(n->get_right());
}

void binary_tree::print::preorder(node *n)
{
    if(n == NULL) return;

    std::cout << n->get_data() << std::endl;
    preorder(n->get_left());
    preorder(n->get_right());
}

void binary_tree::print::postorder(node *n)
{
    if(n == NULL) return;

    postorder(n->get_left());
    postorder(n->get_right());
    std::cout << n->get_data() << std::endl;
}

void binary_tree::print::levelorder(node *n)
{
    if(n == NULL) return;

    std::queue<node *> q;
    q.push(n);

    while(q.empty() == false)
    {
        node *t = q.front();
        q.pop();

        std::cout << t->get_data() << std::endl;
        if(t->get_left() != NULL) q.push(t->get_left());
        if(t->get_right() != NULL) q.push(t->get_right());
    }
}
