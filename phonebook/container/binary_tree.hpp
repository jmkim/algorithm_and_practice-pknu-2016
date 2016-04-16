#ifndef __CONTAINER_BINARYTREE_HPP
#define __CONTAINER_BINARYTREE_HPP    1

namespace container
{
    template<class ELEMENT> struct node
    {
        ELEMENT *element;
        node *left;
        node *right;

        node(void) : element(NULL), left(NULL), right(NULL) {}
        node(ELEMENT *element) : element(element), left(NULL), right(NULL) {}
    };

    template<class NODE, class ELEMENT> class binary_tree
    {
    public:
        virtual bool is_empty(void) const = 0;

    protected:
        static NODE *create_node(const ELEMENT *element);
        static void destroy_node(const NODE *node);

        static void traverse_inorder(const NODE *const node, const std::function<void(const NODE *const)> callback);
        static void traverse_preorder(const NODE *const node, const std::function<void(const NODE *const)> callback);
        static void traverse_postorder(const NODE *const node, const std::function<void(const NODE *const)> callback);
        static void traverse_level_order(const NODE *const node, const std::function<void(const NODE *const)> callback);
    };
}

#endif /* !__CONTAINER_BINARYTREE_HPP */
