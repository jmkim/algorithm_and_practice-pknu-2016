#ifndef __CONTAINER_REDBLACKTREE_HPP
#define __CONTAINER_REDBLACKTREE_HPP    1

namespace container
{
    template<class ELEMENT> struct node_rb : public node_p<ELEMENT>
    {
    public:
        node_rb(void) : node_p<ELEMENT>(), color(true) {}
        node_rb(ELEMENT *element) : node_p<ELEMENT>(element), color(true) {}
        node_rb(ELEMENT *element, node_rb *parent) : node_p<ELEMENT>(element, parent), color(true) {}
        node_rb(ELEMENT *element, node_rb *parent, bool &color) : node_p<ELEMENT>(element, parent), color(color) {}

        bool is_red(void) const;
        bool is_black(void) const;
        bool get_color(void) const;

        void set_red(void);
        void set_black(void);
        void set_color(const bool &color);

    private:
        bool color; /* true: red, false: black */
    };

    template<class NODE, class ELEMENT> class red_black_tree : public binary_search_tree<NODE, ELEMENT>
    {
    public:
        bool is_empty(void) const;
        void insert(const ELEMENT *element);
        void remove(const ELEMENT *element);

    protected:
        NODE *nil;

        red_black_tree(void) : binary_search_tree<NODE, ELEMENT>()
        {
            nil = create_node((NODE *)NULL);
            nil->left = nil->right = nil->parent = nil;
            nil->set_black();
        }
        ~red_black_tree(void) { destroy_node(nil); }

        static void left_rotation(const NODE *node);
        static void right_rotation(const NODE *node);
        static bool is_uncle_red(const NODE *node);
        static void set_uncle_black(const NODE *node);
        static NODE *get_grandparent(const NODE *node);
        static NODE *get_sibling(const NODE *node);

        void insert_rb(NODE *node);
        void remove_rb(NODE *node);
    };
}

#endif /* !__CONTAINER_REDBLACKTREE_HPP */
