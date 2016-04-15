#include <iostream>
#include <functional>
#include <queue>

namespace container
{
    template<typename DATA> class element
    {
    public:
        virtual int set() = 0;
        virtual DATA get() = 0;
        virtual bool compare(element *second) = 0; /* Return true if `me' is less than `second' */
    };

    template<class ELEMENT> class node
    {
    protected:
        ELEMENT *me;
        node *left;
        node *right;

    public:
        node(void) : me(NULL), left(NULL), right(NULL) {}
        node(const ELEMENT *element) : me(element), left(NULL), right(NULL) {}

        void set(const ELEMENT *element) { me = element; }
        void set_left(const node *left) { this->left = left; }
        void set_right(const node *right) { this->right = right; }

        ELEMENT *get(void) const { return me; }
        node *get_left(void) const { return left; }
        node *get_right(void) const { return right; }
    };

    template<class ELEMENT> class node_p : public node<ELEMENT>
    {
    protected:
        node_p *parent;

    public:
        node_p(void) : node<ELEMENT>::node(), parent(NULL) {}
        node_p(const ELEMENT *element) : node<ELEMENT>::node(element), parent(NULL) {}
        node_p(const ELEMENT *element, const node_p *parent) : node<ELEMENT>::node(element), parent(parent) {}

        void set_parent(const node_p *parent) { this->parent = parent; }
        node_p *get_parent(void) const { return parent; }
    };

    template<class ELEMENT> class node_rb : public node_p<ELEMENT>
    {
    protected:
        bool color; /* true: red, false: black */

    public:
        node_rb(void) : node_p<ELEMENT>::node_p(), color(true) {}
        node_rb(const ELEMENT *element) : node_p<ELEMENT>::node_p(element), color(true) {}
        node_rb(const ELEMENT *element, const node_rb *parent) : node_p<ELEMENT>::node_p(element, parent), color(true) {}

        void set_red(void) { color = true; }
        void set_black(void) { color = false; }
        bool is_red(void) const { return color == true; }
        bool is_black(void) const { return color == false; }
    };

    template<class NODE, class ELEMENT> class binary_tree
    {
    public:
        virtual bool is_empty(void) const = 0;

    protected:
        static NODE *create_node(const ELEMENT *element) { return new NODE(element); }
        static void destroy_node(const NODE *node) { delete node; }

        static void traverse_inorder(const NODE *const node, const std::function<void(const NODE *const)> callback)
        {
            if(node == NULL) return; /* Base case */

            traverse_inorder(node->get_left(), callback);
            callback(node);
            traverse_inorder(node->get_right(), callback);
        }

        static void traverse_preorder(const NODE *const node, const std::function<void(const NODE *const)> callback)
        {
            if(node == NULL) return; /* Base case */

            callback(node);
            traverse_preorder(node->get_left(), callback);
            traverse_preorder(node->get_right(), callback);
        }

        static void traverse_postorder(const NODE *const node, const std::function<void(const NODE *const)> callback)
        {
            if(node == NULL) return; /* Base case */

            traverse_postorder(node->get_left(), callback);
            traverse_postorder(node->get_right(), callback);
            callback(node);
        }

        static void traverse_level_order(const NODE *const node, const std::function<void(const NODE *const)> callback)
        {
            NODE *n = node;
            std::queue<NODE *> queue;
            if(n != NULL) queue.push(n);

            while(! queue.empty())
            {
                n = queue.front();
                callback(n);

                queue.pop();
                if(n->get_left() != NULL) queue.push(n->get_left());
                if(n->get_right() != NULL) queue.push(n->get_right());
            }
        }
    };

    template<class NODE, class ELEMENT> class binary_search_tree : public binary_tree<NODE, ELEMENT>
    {
    public:
        bool is_empty(void) const { return root == NULL; }

        NODE *search(const ELEMENT *element)
        {
            NODE *n = NULL;
            traverse_inorder(root, [&] (NODE *node) { if(element == node->get()) n = node; return; });

            return n;
        }

        void insert(const ELEMENT *element) { insert(create_node(element)); }
        void delete_n(const ELEMENT *element) { NODE *node = search(element); delete_n(node); destroy_node(node); }

    protected:
        NODE *root;

        binary_search_tree(void) : root(NULL) {}
        ~binary_search_tree(void) { while(! is_empty()) delete_n(root); }

        static NODE *create_node(const ELEMENT *element) { return new NODE(element); }
        static void destroy_node(const NODE *node) { delete node; }

        NODE *get_minimum(const NODE *node)
        {
            while(node->get_left() != NULL) node = node->get_left();
            return node;
        }

        NODE *get_inorder_successor(const NODE *node)
        {
            /* Downward */
            if(node->get_right() != NULL) return get_minimum(node->get_right());

            /* Upward */
            NODE *n = node;
            NODE *p = node->get_parent();

            while(p != NULL && n == p->get_right())
            {
                n = p;
                p = p->get_parent();
            }

            return p;
        }

        void insert(const NODE *node)
        {
            if(is_empty())
            {
                root = node;
                return;
            }

            NODE *n = root;
            NODE *p = NULL; /* One step previous node of n */

            while(n != NULL)
            {
                p = n;

                if(node->get()->compare(n->get()))
                    n = n->get_left();
                else
                    n = n->get_right();
            }

            if(node->get()->compare(p->get()))
                p->set_left(node);
            else
                p->set_right(node);

            node->set_parent(p);
        }

        void delete_n(const NODE *node)
        {
            if(node == NULL) return; /* Not exists */

            if(node->get_left() != NULL && node->get_right() != NULL)
            {
                NODE *s = get_inorder_successor(node);
                if(s->get_parent() != NULL) s->get_parent()->set_right(s->get_right());

                if(node->get_parent() == NULL)
                    root = s;
                else
                {
                    if(node->get_parent()->get_left() == node)
                        node->get_parent()->set_left(s);
                    else
                        node->get_parent()->set_right(s);
                }

                s->set_left(node->get_left());
                s->set_right(node->get_right());
                s->set_parent(node->get_parent());
            }
            else
            {
                if(node->get_parent() == NULL)
                    root = NULL;
                else
                {
                    if(node->get_parent()->get_left() == node)
                        node->get_parent()->set_left(node->get_left());
                    else
                        node->get_parent()->set_right(node->get_right());
                }
            }
        }
    };

    template<class NODE, class ELEMENT> class red_black_tree : public binary_search_tree<NODE, ELEMENT>
    {
    public:
        bool is_empty(void) const { return binary_search_tree<NODE, ELEMENT>::root == nil; }
        void insert(const ELEMENT *element) { insert_rb(create_node(element)); }
        void delete_n(const ELEMENT *element) { NODE *node = search(element); delete_rb(node); destroy_node(node); }

    protected:
        NODE *nil;

        red_black_tree(void)
        {
            nil = create_node("");
            nil->set_left(nil);
            nil->set_right(nil);
            nil->set_parent(nil);
            nil->set_black();
        }
        ~red_black_tree(void) { destroy_node(nil); }

        static NODE *create_node(const ELEMENT *element) { return new NODE(element); }
        static void destroy_node(const NODE *node) { delete node; }

        static void left_rotation(NODE *node)
        {
            const NODE *pivot = node->get_right();
            const NODE *parent = node->get_parent();

            /* Swap the position of `node' node and `pivot' node */
            {
                node->set_right(pivot->get_left()); /* Change `node.right' to point `pivot.left' */
                pivot->set_left(node); /* Change `pivot.left' to point `node' */
                node->set_parent(pivot); /* Change `node.parent' to point `pivot' */
            }

            /* Change the child of `parent' node */
            if(parent->get_left() == node)
                parent->set_left(pivot);
            else
                parent->set_right(pivot);
        }

        static void right_rotation(const NODE *node)
        {
            const NODE *pivot = node->get_left();
            const NODE *parent = node->get_parent();

            /* Swap the position of `node' node and `pivot' node */
            {
                node->set_left(pivot->get_right()); /* Change `node.left' to point `pivot.right' */
                pivot->set_right(node); /* Change `pivot.right' to point `node' */
                node->set_parent(pivot); /* Change `node.parent' to point `pivot' */
            }

            /* Change the child of `parent' node */
            if(parent->get_left() == node)
                parent->set_left(pivot);
            else
                parent->set_right(pivot);
        }

        static NODE *get_grandparent(const NODE *node)
        {
            return node->get_parent()->get_parent();
        }

        static bool is_uncle_red(const NODE *node)
        {
            NODE *grandparent = get_grandparent(node);

            if(grandparent->get_left() != node->get_parent())
                return grandparent->get_left()->is_red();
            else
                return grandparent->get_right()->is_red();
        }

        static void set_uncle_black(const NODE *node)
        {
            NODE *grandparent = get_grandparent(node);

            if(grandparent->get_left() != node->get_parent())
                return grandparent->get_left()->set_black();
            else
                return grandparent->get_right()->set_black();
        }

        static NODE *get_sibling(const NODE *node)
        {
            if(node->get_parent()->get_left() == node)
                return node->get_parent()->get_right();
            else
                return node->get_parent()->get_left();
        }

        void insert_rb(NODE *node)
        {
            insert(node); /* Call the BST insertion */

            /* Set the NIL node */
            if(node->get_left() == NULL) node->set_left(nil);
            if(node->get_right() == NULL) node->set_right(nil);
            if(node->get_parent() == NULL) node->set_parent(nil);

            while(node->is_red())
            {
                if(node->get_parent()->is_red()) 
                {
                    if(is_uncle_red(node))
                    {
                        node->get_parent()->set_black();
                        set_uncle_black(node);
                        get_grandparent(node)->set_red();

                        node = get_grandparent(node);
                    }
                    else
                    {
                        if(get_grandparent(node)->get_left() == node->get_parent(node))
                        {
                            if(node->get_parent()->get_right() == node)
                                left_rotation(node->get_parent());

                            right_rotation(node->get_parent());
                            node->get_right()->set_red();
                        }
                        else
                        {
                            if(node->get_parent()->get_left() == node)
                                right_rotation(node->get_parent());

                            left_rotation(node->get_parent());
                            node->get_left()->set_red();
                        }

                        node->set_black();
                        break;
                    }
                }
                else
                    break;
            }

            if(binary_search_tree<ELEMENT, NODE>::root->is_red()) binary_search_tree<ELEMENT, NODE>::root->set_black();
        }

        void delete_rb(NODE *node)
        {
            if(node == nil) return; /* Not exists */

            NODE *del;
            if(node->get_left() != nil && node->get_right() != nil)
            {
                del = get_successor(node);
                node->set(del->get());
            }
            else
                del = node;

            NODE *temp;
            if(node->get_parent()->get_left() == node)
                temp = del->get_left();
            else
                temp = del->get_right();

            NODE *py = del->get_parent();

            delete_n(del); /* Call the BST deletion*/

            if(del->is_red()) return;

            while(temp != binary_search_tree<NODE, ELEMENT>::root && temp->is_black())
            {
                NODE *parent;
                if(temp == nil)
                    parent = py;
                else
                    parent = temp->get_parent();

                NODE *sibling;
                if(temp == parent->get_left())
                {
                    sibling = parent->get_right();

                    if(sibling->is_red())
                    {
                        /* CASE ONE */
                        sibling->set_black();
                        parent->set_red();
                        left_rotation(parent);
                        sibling = parent->get_right();
                    }

                    if(sibling->get_left()->is_black() && sibling->get_right()->is_black())
                    {
                        /* CASE TWO */
                        sibling->set_red();
                        temp = parent;
                    }
                    else
                    {
                        if(sibling->get_right()->is_black())
                        {
                            /* CASE THREE */
                            sibling->set_black();
                            sibling->set_red();
                            right_rotation(sibling);
                            sibling = parent->right();
                        }

                        /* CASE FOUR */
                        if(parent->is_black())
                            sibling->set_black();
                        else
                            sibling->set_red();

                        parent->set_black();
                        sibling->get_right()->set_black();

                        left_rotation(parent);

                        temp = binary_search_tree<NODE, ELEMENT>::root;
                    }
                }
                else
                {
                    /* DIRECTION CONVERSION */

                    sibling = parent->get_left();
                    if(sibling->is_red())
                    {
                        sibling->set_black();
                        parent->set_red();

                        right_rotation(parent);

                        sibling = parent->get_left();
                    }

                    if(sibling->get_left()->is_black() && sibling->get_right()->is_black())
                    {
                        sibling->set_red();
                        temp = parent;
                    }
                    else
                    {
                        if(sibling->get_left()->is_black())
                        {
                            sibling->get_right->set_black();
                            sibling->set_red();

                            left_rotation(sibling);

                            sibling = parent->get_left();
                        }

                        if(parent->is_black())
                            sibling->set_black();
                        else
                            sibling->set_red();

                        parent->set_black();
                        sibling->get_left()->set_black();

                        right_rotation(parent);

                        temp = binary_search_tree<NODE, ELEMENT>::root;
                    }
                }
            }

            temp->set_black();
        }
    };
}
