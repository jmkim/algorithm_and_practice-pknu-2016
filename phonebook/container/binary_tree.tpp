using namespace container;

template<class NODE, class ELEMENT> NODE *binary_tree<NODE, ELEMENT>::create_node(const ELEMENT *element) { return new NODE(element); }
template<class NODE, class ELEMENT> void binary_tree<NODE, ELEMENT>::destroy_node(const NODE *node) { delete node; }

template<class NODE, class ELEMENT> void binary_tree<NODE, ELEMENT>::traverse_inorder(const NODE *const node, const std::function<void(const NODE *const)> callback)
{
    if(node == NULL) return; /* Base case */

    traverse_inorder(node->left, callback);
    callback(node);
    traverse_inorder(node->right, callback);
}

template<class NODE, class ELEMENT> void binary_tree<NODE, ELEMENT>::traverse_preorder(const NODE *const node, const std::function<void(const NODE *const)> callback)
{
    if(node == NULL) return; /* Base case */

    callback(node);
    traverse_preorder(node->left, callback);
    traverse_preorder(node->right, callback);
}

template<class NODE, class ELEMENT> void binary_tree<NODE, ELEMENT>::traverse_postorder(const NODE *const node, const std::function<void(const NODE *const)> callback)
{
    if(node == NULL) return; /* Base case */

    traverse_postorder(node->left, callback);
    traverse_postorder(node->right, callback);
    callback(node);
}

template<class NODE, class ELEMENT> void binary_tree<NODE, ELEMENT>::traverse_level_order(const NODE *const node, const std::function<void(const NODE *const)> callback)
{
    NODE *n = node;
    std::queue<NODE *> queue;
    if(n != NULL) queue.push(n);

    while(! queue.empty())
    {
        n = queue.front();
        callback(n);

        queue.pop();
        if(n->left != NULL) queue.push(n->left);
        if(n->right != NULL) queue.push(n->right);
    }
}
