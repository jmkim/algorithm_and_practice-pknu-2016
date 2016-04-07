#include <string>

#include "node.hpp"

std::string binary_tree::node::carrtostr(const char carr[])
{
    std::string str;

    for(int i = 0; carr[i] != '\0'; ++i)
        str.push_back(carr[i]);

    return str;
}

binary_tree::node::node(const char data[])
{
    set_data(carrtostr(data));

    left = NULL;
    right = NULL;
}

binary_tree::node::node(std::string &data)
{
    set_data(data);

    left = NULL;
    right = NULL;
}

binary_tree::node::~node(void) {}

void binary_tree::node::set_data(const char data[]) { this->data = carrtostr(data); }
void binary_tree::node::set_data(std::string data) { this->data = data; }
void binary_tree::node::set_left(node *node) { left = node; }
void binary_tree::node::set_right(node *node) { right = node; }

std::string binary_tree::node::get_data(void) const { return data; }
binary_tree::node *binary_tree::node::get_left(void) const { return left; }
binary_tree::node *binary_tree::node::get_right(void) const { return right; }
