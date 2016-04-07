#include <iostream>
#include <string>

#include "binary_tree/node.hpp"
#include "binary_tree/print.hpp"

using namespace binary_tree;

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
