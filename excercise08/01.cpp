#include <iostream>
#include <string>
#include <queue>

namespace excercise08
{
    class node
    {
    private:
        std::string data;
        node *left;
        node *right;
        static std::string carrtostr(const char carr[])
        {
            std::string str;

            for(int i = 0; carr[i] != '\0'; ++i)
                str.push_back(carr[i]);

            return str;
        }
    public:
        node(const char data[])
        {
            set_data(carrtostr(data));

            left = NULL;
            right = NULL;
        }
        node(std::string &data)
        {
            set_data(data);

            left = NULL;
            right = NULL;
        }
        ~node(void) {}

        void set_data(const char data[]) { this->data = carrtostr(data); }
        void set_data(std::string data) { this->data = data; }
        void set_left(node *node) { left = node; }
        void set_right(node *node) { right = node; }

        std::string get_data(void) const { return data; }
        node *get_left(void) const { return left; }
        node *get_right(void) const { return right; }
    };

    class print
    {
    public:
        static void inorder(node *n)
        {
            if(n == NULL) return;

            inorder(n->get_left());
            std::cout << n->get_data() << std::endl;
            inorder(n->get_right());
        }

        static void preorder(node *n)
        {
            if(n == NULL) return;

            std::cout << n->get_data() << std::endl;
            preorder(n->get_left());
            preorder(n->get_right());
        }

        static void postorder(node *n)
        {
            if(n == NULL) return;

            postorder(n->get_left());
            postorder(n->get_right());
            std::cout << n->get_data() << std::endl;
        }

        static void levelorder(node *n)
        {
            if(n == NULL) return;

            std::queue<node *> q;
            q.push(n);

            while(q.empty() == false)
            {
                node *t = q.front();
                q.pop();

                std::cout << t->get_data() << std::endl;
                if(t->get_left() != NULL) q.push(t->get_left());
                if(t->get_right() != NULL) q.push(t->get_right());
            }
        }
    };
}

using namespace excercise08;

int main(void)
{
    node root("fox");

    node bear("bear");
    root.set_left(&bear);

    node ant("ant");
    bear.set_left(&ant);

    node dog("dog");
    bear.set_right(&dog);

    node cat("cat");
    dog.set_left(&cat);

    node eagle("eagle");
    dog.set_right(&eagle);

    node goose("goose");
    root.set_right(&goose);

    node hippo("hippo");
    goose.set_right(&hippo);

    node iguana("iguana");
    hippo.set_right(&iguana);

    std::cout << "Inorder" << std::endl;
    print::inorder(&root);

    std::cout << std::endl << "Preorder" << std::endl;
    print::preorder(&root);

    std::cout << std::endl << "Postorder" << std::endl;
    print::postorder(&root);

    std::cout << std::endl << "Level-order" << std::endl;
    print::levelorder(&root);

    return 0;
}
