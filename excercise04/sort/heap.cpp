#include "heap.hpp"
#include "swap.hpp"

void convert_to_binary_max_heap(int *data, const int size_of_data)
{
    for(int i = size_of_data - 1; i > 0; --i)
    {
        for(int k = i; k > 0; k = (k - 1) / 2)
            if(data[i] > data[(k - 1) / 2]) swap(data[i], data[(k - 1) / 2]);
    }
}
