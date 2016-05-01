#include <iostream>

#define GRAPH_NODETYPE   1
#include "src/graph.hpp"

int main(void)
{
    int arr[5][5] =
    {
        0, 1, 0, 0, 1,
        1, 0, 1, 1, 1,
        0, 1, 0, 1, 0,
        0, 1, 1, 0, 1,
        1, 1, 0, 1, 0
    };

    graph<int> g(25, [] (const int &a, const int &b) { return a == b; });

    for(int i = 0; i < 5; ++i) g.add_vertex(i + 1);
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            if(arr[i][j] == 1)
            {
                g.add_edge(i, j);
                g.add_edge(j, i);
            }
        }
    }
    g.print();
}
