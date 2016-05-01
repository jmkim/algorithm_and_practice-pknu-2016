using namespace container;

template<class ELEMENT> bool node_rb<ELEMENT>::is_red(void) const { return color == true; }
template<class ELEMENT> bool node_rb<ELEMENT>::is_black(void) const { return color == false; }
template<class ELEMENT> bool node_rb<ELEMENT>::get_color(void) const { return color; }

template<class ELEMENT> void node_rb<ELEMENT>::set_red(void) { color = true; }
template<class ELEMENT> void node_rb<ELEMENT>::set_black(void) { color = false; }
template<class ELEMENT> void node_rb<ELEMENT>::set_color(const bool &color) { this->color = color; }

template<class NODE, class ELEMENT> bool red_black_tree<NODE, ELEMENT>::is_empty(void) const { return this->root == nil; }
template<class NODE, class ELEMENT> void red_black_tree<NODE, ELEMENT>::insert(const ELEMENT *element) { insert_rb(create_node(element)); }
template<class NODE, class ELEMENT> void red_black_tree<NODE, ELEMENT>::remove(const ELEMENT *element)
{
    NODE *node = search(element);
    remove_rb(node);
    destroy_node(node);
}

template<class NODE, class ELEMENT> void red_black_tree<NODE, ELEMENT>::left_rotation(const NODE *node)
{
    const NODE *pivot = node->right;
    const NODE *parent = node->parent;

    /* Swap the position of `node' node and `pivot' node */
    {
        node->right = pivot->left; /* Change `node.right' to point `pivot.left' */
        pivot->left = node; /* Change `pivot.left' to point `node' */
        node->parent = pivot; /* Change `node.parent' to point `pivot' */
    }

    /* Change the child of `parent' node */
    if(parent->left == node)
        parent->left = pivot;
    else
        parent->right = pivot;
}

template<class NODE, class ELEMENT> void red_black_tree<NODE, ELEMENT>::right_rotation(const NODE *node)
{
    const NODE *pivot = node->left;
    const NODE *parent = node->parent;

    /* Swap the position of `node' node and `pivot' node */
    {
        node->left = pivot->right; /* Change `node.left' to point `pivot.right' */
        pivot->right = node; /* Change `pivot.right' to point `node' */
        node->parent = pivot; /* Change `node.parent' to point `pivot' */
    }

    /* Change the child of `parent' node */
    if(parent->left == node)
        parent->left = pivot;
    else
        parent->right = pivot;
}

template<class NODE, class ELEMENT> NODE *red_black_tree<NODE, ELEMENT>::get_grandparent(const NODE *node)
{
    return node->parent->parent;
}

template<class NODE, class ELEMENT> bool red_black_tree<NODE, ELEMENT>::is_uncle_red(const NODE *node)
{
    NODE *grandparent = get_grandparent(node);

    if(grandparent->left != node->parent)
        return grandparent->left->is_red();
    else
        return grandparent->right->is_red();
}

template<class NODE, class ELEMENT> void red_black_tree<NODE, ELEMENT>::set_uncle_black(const NODE *node)
{
    NODE *grandparent = get_grandparent(node);

    if(grandparent->left != node->parent)
        return grandparent->left->set_black();
    else
        return grandparent->right->set_black();
}

template<class NODE, class ELEMENT> NODE *red_black_tree<NODE, ELEMENT>::get_sibling(const NODE *node)
{
    if(node->parent->left != node)
        return node->parent->left;
    else
        return node->parent->right;
}

template<class NODE, class ELEMENT> void red_black_tree<NODE, ELEMENT>::insert_rb(NODE *node)
{
    insert(node); /* Call the BST insertion */

    /* Set the NIL node */
    if(node->left == NULL) node->left = nil;
    if(node->right == NULL) node->right = nil;
    if(node->parent == NULL) node->parent = nil;

    while(node->is_red())
    {
        if(node->parent->is_red())
        {
            if(is_uncle_red(node))
            {
                node->parent->set_black();
                set_uncle_black(node);
                get_grandparent(node)->set_red();

                node = get_grandparent(node);
            }
            else
            {
                if(get_grandparent(node)->left == node->parent)
                {
                    if(node->parent->right == node)
                        left_rotation(node->parent);

                    right_rotation(node->parent);
                    node->right->set_red();
                }
                else
                {
                    if(node->parent->left == node)
                        right_rotation(node->parent);

                    left_rotation(node->parent);
                    node->left->set_red();
                }

                node->set_black();
                break;
            }
        }
        else
            break;
    }

    if(this->root->is_red()) this->root->set_black();
}

template<class NODE, class ELEMENT> void red_black_tree<NODE, ELEMENT>::remove_rb(NODE *node)
{
    if(node == nil) return; /* Not exists */

    NODE *del;
    if(node->left != nil && node->right != nil)
    {
        del = get_inorder_successor(node);
        node->element = del->element;
    }
    else
        del = node;

    NODE *temp;
    if(node->parent->left == node)
        temp = del->left;
    else
        temp = del->right;

    NODE *py = del->parent;

    remove(del); /* Call the BST deletion*/

    if(del->is_red()) return;

    while(temp != this->root && temp->is_black())
    {
        NODE *parent;
        if(temp == nil)
            parent = py;
        else
            parent = temp->parent;

        NODE *sibling;
        if(temp == parent->left)
        {
            sibling = parent->right;

            if(sibling->is_red())
            {
                /* CASE ONE */
                sibling->set_black();
                parent->set_red();
                left_rotation(parent);
                sibling = parent->right;
            }

            if(sibling->left->is_black() && sibling->right->is_black())
            {
                /* CASE TWO */
                sibling->set_red();
                temp = parent;
            }
            else
            {
                if(sibling->right->is_black())
                {
                    /* CASE THREE */
                    sibling->set_black();
                    sibling->set_red();
                    right_rotation(sibling);
                    sibling = parent->right;
                }

                /* CASE FOUR */
                if(parent->is_black())
                    sibling->black;
                else
                    sibling->red;

                parent->set_black();
                sibling->right->set_black();

                left_rotation(parent);

                temp = this->root;
            }
        }
        else
        {
            /* DIRECTION CONVERSION */

            sibling = parent->left;
            if(sibling->is_red())
            {
                sibling->set_black();
                parent->set_red();

                right_rotation(parent);

                sibling = parent->left;
            }

            if(sibling->left->is_black() && sibling->right->is_black())
            {
                sibling->set_red();
                temp = parent;
            }
            else
            {
                if(sibling->left->is_black())
                {
                    sibling->right->set_black();
                    sibling->set_red();

                    left_rotation(sibling);

                    sibling = parent->left;
                }

                if(parent->is_black())
                    sibling->set_black();
                else
                    sibling->set_red();

                parent->set_black();
                sibling->left->set_black();

                right_rotation(parent);

                temp = this->root;
            }
        }
    }

    temp->set_black();
}
