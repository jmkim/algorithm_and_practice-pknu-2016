#ifndef __CONTACTMANAGER_HPP
#define __CONTACTMANAGER_HPP     1

class contact_manager
{
private:
    binary_tree::node *data;

    binary_tree::node *new_node(contact *contact);
    void delete_node(binary_tree::node *node);

    void clear_all_child(binary_tree::node *node);
    binary_tree::node *get_node_by_name(const std::string &name, binary_tree::node *node);
    binary_tree::node *get_tree_minimum(binary_tree::node *x);
    binary_tree::node *get_tree_successor(binary_tree::node *x);

public:
    ~contact_manager(void);

    void add(contact *c);
    void remove(const std::string &name);
    void find(const std::string &name);
    void print(void);
=======
    binary_tree::node *data;

    binary_tree::node *new_node(contact *contact);
    void delete_node(binary_tree::node *node);

    void clear_all_child(binary_tree::node *node);
    binary_tree::node *get_node_by_name(const std::string &name, binary_tree::node *node);
    binary_tree::node *get_tree_minimum(binary_tree::node *x);
    binary_tree::node *get_tree_successor(binary_tree::node *x);

public:
    ~contact_manager(void);

    void add(contact *c);
    void remove(const std::string &name);
    void find(const std::string &name);
    void print(binary_tree::node *d);
    void printall(void);
    void printall(binary_tree::node *node);
>>>>>>> draft/phonebook
    //void sort(const int key); /* Not implemented */
};

#endif /* !__CONTACTMANAGER_HPP */
