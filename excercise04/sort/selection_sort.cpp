#include "selection_sort.hpp"
#include "swap.hpp"

void selection_sort(int *data, const int size_of_data)
{
    for(int i = 0; i < size_of_data; ++i)
    {
        int min = i;
        for(int j = i; j < size_of_data; ++j)
            if(data[j] < data[min]) min = j;

        swap(data[i], data[min]);
    }
}

