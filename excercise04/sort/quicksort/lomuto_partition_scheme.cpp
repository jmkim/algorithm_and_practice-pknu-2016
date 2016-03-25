#include "../quick.hpp"
#include "../swap.hpp"

void quick(int *data, const int size_of_data)
{
    return quick(data, 0, size_of_data - 1);
}

void quick(int *data, const int start, const int end)
{
    if(start >= end) return;

    int small = start;
    for(int i = start; i < end; ++i)
        if(data[i] < data[end]) swap(data[i], data[small++]);

    swap(data[small], data[end]);

    quick(data, start, small - 1);
    quick(data, small + 1, end);
}
