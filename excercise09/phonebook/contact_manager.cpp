#include <iostream>
#include <string>
#include <algorithm> /* sort(iter, iter, bool) */
#include <array>
#include <vector>

#include "../../excercise07/phonebook/keyname.hpp"
#include "../../excercise07/phonebook/strtool.hpp"
#include "../../excercise07/phonebook/contact.hpp"
#include "node.hpp"
#include "../../excercise08/binary_tree/print.hpp"
#include "contact_manager.hpp"

contact_manager::~contact_manager(void)
{
    clear_all_child(data);
}

binary_tree::node *contact_manager::new_node(contact *contact) { return new binary_tree::node(contact, NULL); }
void contact_manager::delete_node(binary_tree::node *node) { delete node; }

void contact_manager::clear_all_child(binary_tree::node *node)
{
    /* Postorder */
    if(node == NULL) return;

    clear_all_child(node->get_left());
    clear_all_child(node->get_right());
    delete_node(node);
}

binary_tree::node *contact_manager::get_node_by_name(const std::string &name, binary_tree::node *node)
{
    /* Inorder */
    if(node == NULL || name == node->get_data()->get(NAME)) return node;

    if(name < node->get_data()->get(NAME))
        get_node_by_name(name, node->get_left());
    else
        get_node_by_name(name, node->get_right());
}

binary_tree::node *contact_manager::get_tree_minimum(binary_tree::node *x)
{
    while(x->get_left() != NULL)
        x = x->get_left();

    return x;
}

binary_tree::node *contact_manager::get_tree_successor(binary_tree::node *x)
{
    if(x->get_right() != NULL) return get_tree_minimum(x->get_right());

    binary_tree::node *y = x->get_parent();

    while(y != NULL && x == y->get_right())
    {
        x = y;
        y = y->get_parent();
    }

    return y;
}

void contact_manager::add(contact *c)
{
    if(get_node_by_name(c->get(NAME), data) != NULL) return; /* Already exists */

    binary_tree::node *newnode = new_node(c);

    binary_tree::node *y = NULL;
    binary_tree::node *x = data;

    while(x != NULL)
    {
        y = x;

        {
            if(newnode->get_data()->get(NAME) < x->get_data()->get(NAME))
                x = x->get_left();
            else
                x = x->get_right();
        }
    }

    newnode->set_parent(y);

    {
        if(y == NULL)
            data = newnode;
        else if(newnode->get_data()->get(NAME) < y->get_data()->get(NAME))
            y->set_left(newnode);
        else
            y->set_right(newnode);
    }
}

void contact_manager::remove(const std::string &name)
{
    binary_tree::node *t = get_node_by_name(name, data);
    if(t == NULL) return; /* Not exists */

    binary_tree::node *y;
    binary_tree::node *x;
    {
        if(t->get_left() == NULL || t->get_right() == NULL)
            y = t;
        else
            y = get_tree_successor(t);
    }

    {
        if(t->get_left() != NULL)
            x = y->get_left();
        else
            x = y->get_right();
    }

    {
        if(x != NULL) x->set_parent(y->get_parent());
    }

    {
        if(y->get_parent() == NULL)
            data = x;
        else if(y == y->get_parent()->get_left())
            y->get_parent()->set_left(x);
        else
            y->get_parent()->set_right(x);
    }

    {
        if(y != t) t->set_data(y->get_data());
    }

    delete_node(y);
}

void contact_manager::find(const std::string &name)
{
    print(get_node_by_name(name, data));
}

void contact_manager::printall(void)
{
    printall(data);
}

void contact_manager::printall(binary_tree::node *node)
{
    /* Inorder */
    if(node == NULL) return;

    printall(node->get_left());
    print(node);;
    printall(node->get_right());
}

void contact_manager::print(binary_tree::node *d)
{
    if(d == NULL) return;
    std::cout   << d->get_data()->get(NAME) << std::endl
                << "\tCompany: " << d->get_data()->get(COMPANY) << std::endl
                << "\tAddress: " << d->get_data()->get(ADDRESS) << std::endl
                << "\tZipcode: " << d->get_data()->get(ZIPCODE) << std::endl
                << "\tPhones:  " << d->get_data()->get(PHONE_PRIMARY) << ", " << d->get_data()->get(PHONE_SECONDARY) << std::endl
                << "\tEmail:   " << d->get_data()->get(EMAIL) << std::endl
                << "\tWeb:     " << d->get_data()->get(WEB) << std::endl
                << std::endl;
}
