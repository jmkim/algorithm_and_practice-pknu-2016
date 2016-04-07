#ifndef __BINARYTREE_NODE_HPP
#define __BINARYTREE_NODE_HPP   1

namespace binary_tree
{
    class node
    {
    private:
        std::string data;
        node *left;
        node *right;
        static std::string carrtostr(const char carr[]);

    public:
        node(const char data[]);
        node(std::string &data);
        ~node(void);

        void set_data(const char data[]);
        void set_data(std::string data);
        void set_left(node *node);
        void set_right(node *node);

        std::string get_data(void) const;
        node *get_left(void) const;
        node *get_right(void) const;
    };
}

#endif /* !__BINARYTREE_NODE_HPP */
