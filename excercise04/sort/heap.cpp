#include "heap.hpp"
#include "swap.hpp"

void binary_max_heap(int *data, const int end)
{
    for(int i = end; i > 0; --i)
    {
        for(int k = i; k > 0; k = (k - 1) / 2)
            if(data[i] > data[(k - 1) / 2]) swap(data[i], data[(k - 1) / 2]);
    }
}
