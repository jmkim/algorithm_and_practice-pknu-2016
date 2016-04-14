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
    private:
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
    private:
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

        void insert(const DATA &key)
        {
            NODE *node = create_node(key);
            if(is_empty()) root = node;

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

            if(node->get_left != NULL && node->get_right != NULL)
            {
                NODE *s = get_inorder_successor(node);
                if(s->get_parent() != NULL) s->get_parent()->set_right(s->get_right());

                s->set_left(node->get_left());
                s->set_right(node->get_right());

                if(node->get_parent() == NULL)
                    root = n;
                else
                {
                    if(node->get_parent()->get_left() == node)
                        node->get_parent()->set_left(s);
                    else
                        node->get_parent()->set_right(s);
                }
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

            destroy_node(node);
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

        void delete(const DATA &key) { delete(search(key)); }
    };
}
