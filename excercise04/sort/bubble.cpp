#include "bubble.hpp"
#include "swap.hpp"

void bubble(int *data, int size_of_data)
{
    for(int i = 0; i < size_of_data; ++i)
        if(data[i] > data[i + 1]) swap(data[i], data[i + 1]);

    return bubble(data, size_of_data - 1);
}

