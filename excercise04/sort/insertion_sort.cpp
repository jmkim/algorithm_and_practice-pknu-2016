#include "insertion_sort.hpp"
#include "swap.hpp"

void insertion_sort(int *data, const int size_of_data)
{
    for(int i = 0; i < size_of_data; ++i)
    {
        for(int j = i; j > 0 && data[j] < data[j - 1]; --j) swap(data[j], data[j - 1]);
    }
}

