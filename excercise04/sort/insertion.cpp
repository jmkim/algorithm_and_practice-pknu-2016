#include "insertion.hpp"
#include "swap.hpp"

void insertion(int *data, int size_of_data)
{
    for(int i = 0; i < size_of_data; ++i)
    {
        int j;
        for(j = i; data[j] < data[i]; --j);
        swap(data[i], data[j]);
    }
}

