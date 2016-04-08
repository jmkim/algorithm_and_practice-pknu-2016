#include <string>

#include "../../excercise07/phonebook/contact.hpp"
#include "node.hpp"

binary_tree::node::node(const contact &data, const node *parent)
{
    this->data = new contact;
    *this->data = data;

    left = NULL;
    right = NULL;
    this->parent = parent;
}

binary_tree::node::~node(void)
{
    delete data;
}

void binary_tree::node::set_data(const contact &data) { *this->data = data; }
void binary_tree::node::set_left(node *node) { left = node; }
void binary_tree::node::set_right(node *node) { right = node; }
void binary_tree::node::set_parent(node *node) { parent = node; }

contact *binary_tree::node::get_data(void) const { return data; }
binary_tree::node *binary_tree::node::get_left(void) const { return left; }
binary_tree::node *binary_tree::node::get_right(void) const { return right; }
binary_tree::node *binary_tree::node::get_parent(void) const { return parent; }
