#ifndef __BINARYTREE_PRINT_HPP
#define __BINARYTREE_PRINT_HPP   1

namespace binary_tree
{
    struct print
    {
        static void inorder(const node *n);
        static void preorder(const node *n);
        static void postorder(const node *n);
        static void levelorder(node *n);
    };
}

#endif /* !__BINARYTREE_PRINT_HPP */
