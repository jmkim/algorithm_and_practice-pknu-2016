#include "src/city_searcher.hpp"

int main(const int argc, const char *argv[])
{
    city_searcher cs;
    cs.load(argc, argv);
    cs.prompt();

    return 0;
}
