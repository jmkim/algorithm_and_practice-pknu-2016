#ifndef __BINARYTREE_NODE_HPP
#define __BINARYTREE_NODE_HPP   1

namespace binary_tree
{
    class node
    {
    private:
        contact *data;
        node *left;
        node *right;

    public:
        node(const contact &data);
        ~node(void);

        void set_data(const contact &data);
        void set_left(node *node);
        void set_right(node *node);

        std::string get_data(void) const;
        node *get_left(void) const;
        node *get_right(void) const;
    };
}

#endif /* !__BINARYTREE_NODE_HPP */
