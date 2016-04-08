#include <string>

#include "node.hpp"

binary_tree::node::node(const std::string data)
{
    set_data(data);

    left = NULL;
    right = NULL;
}

binary_tree::node::~node(void) {}

void binary_tree::node::set_data(const std::string data) { this->data = data; }
void binary_tree::node::set_left(node *node) { left = node; }
void binary_tree::node::set_right(node *node) { right = node; }

std::string binary_tree::node::get_data(void) const { return data; }
binary_tree::node *binary_tree::node::get_left(void) const { return left; }
binary_tree::node *binary_tree::node::get_right(void) const { return right; }
