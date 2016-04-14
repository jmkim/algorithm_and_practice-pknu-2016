#include <functional>
#include <queue>

namespace container
{
    template<typename DATA> class element
    {
    public:
        virtual void set(const DATA &key) = 0;
        virtual DATA get(void) = 0;
    };

    template<class ELEMENT, typename DATA> class node
    {
    protected:
        ELEMENT *me;
        node *left;
        node *right;

    public:
        node(const DATA &key)
        {
            me = new ELEMENT(key);
            left = NULL;
            right = NULL;
        }
        ~node(void) { delete me; }

        void set(const DATA &key) { me->set(key); }
        void set_left(const node *left) { this->left = left; }
        void set_right(const node *right) { this->right = right; }

        DATA get(void) const { return me->get() }
        node *get_left(void) const { return left; }
        node *get_right(void) const { return right; }
    }

    template<class ELEMENT, typename DATA> class node_p : public node
    {
    protected:
        node_p *parent;

    public:
        node_p(const DATA &key)
        {
            me = new ELEMENT(key);
            left = NULL;
            right = NULL;
            parent = NULL;
        }
        node_p(const DATA &key, const node_p *parent)
        {
            me = new ELEMENT(key);
            left = NULL;
            right = NULL;
            this->parent = parent;
        }
        ~node_p(void) { delete me; }

        void set_parent(const node_p *parent) { this->right = right; }
        node_p *get_parent(void) const { return parent; }
    };

    template<class ELEMENT, typename DATA> class node_rb : public node_p
    {
    protected:
        bool is_color_black;

    public:
        node_p(const DATA &key) : is_color_black(false)
        {
            me = new ELEMENT(key);
            left = NULL;
            right = NULL;
            parent = NULL;
        }
        node_p(const DATA &key, const node_p *parent) : is_color_black(false)
        {
            me = new ELEMENT(key);
            left = NULL;
            right = NULL;
            this->parent = parent;
        }
        ~node_p(void) { delete me; }

        void set_black(void) { is_color_black = true; }
        void set_red(void) { is_color_black = false; }
        bool is_black(void) const { return is_color_black; }
        bool is_red(void) const { return ! is_color_black; }
    };

    template<class NODE, typename DATA> class binary_tree
    {
    protected:
        static NODE *create_node(const DATA &key) { return new NODE(key); }
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

    public:
        virtual bool is_empty(void) const = 0;
        virtual int get_size(void) const = 0;
    };

    template<class NODE, typename DATA> class binary_search_tree : public binary_tree<NODE, DATA>
    {
    protected:
        NODE *root;
        int size;

        binary_search_tree(void) : size(0) { root = NULL; }
        ~binary_search_tree(void) { while(! is_empty()) delete(root); }

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

                if(node->get() < n->get())
                    n = n->get_left();
                else
                    n = n->get_right();
            }

            if(node->get() < p->get())
                p->set_left(node);
            else
                p->set_right(node);

            node->set_parent(p);
        }

        void delete(const NODE *node)
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

    public:
        bool is_empty(void) const { return root == NULL; }
        int get_size(void) const { return size; }

        NODE *search(const DATA &key)
        {
            NODE *n = NULL;
            traverse_inorder(root,
                [&] (NODE *node) => { if(key == node->get()->get()) n = node; return; }
            );

            return n;
        }

        void insert(const DATA &key) { insert(create_node(key)); }
        void delete(const DATA &key) { NODE *node = search(key); delete(node); destroy_node(node); }
    };

    template<class NODE, typename DATA> class red_black_tree : public binary_search_tree<NODE, DATA>
    {
    private:
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
            if(node->get_parent() == nil) return nil;
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

            if(root->is_red()) root->set_black();
        }

        void delete(NODE *node)
        {
            if(node == NULL) return; /* Not exists */

            /* Section of BST deletion */
            {
            }
        }

    public:
        void insert(const DATA &key) { insert_rb(create_node(key)); }

    };
}
