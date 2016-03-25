#include "../quick.hpp"
#include "../swap.hpp"

void quick(int *data, const int size_of_data)
{
    return quick(data, 0, size_of_data - 1);
}

void quick(int *data, const int start, const int end)
{
    if(start >= end) return; /* Base case */

    /* Conquer */
    int pivot = partition(data, start, end);

    /* Divide */
    quick(data, start, pivot - 1);
    quick(data, pivot + 1, end);
}

int partition(int *data, const int start, const int end)
{
    int pivot = end; /* Set pivot */

    int pleft = start,
        pright = end - 1;

    while(pleft != pright)
    {
        while(pleft < pright && data[pleft] <= data[pivot]) ++pleft;
        while(pleft < pright && data[pright] >= data[pivot]) --pright;

        if(pleft < pright) swap(data[pleft], data[pright]);
    }

    if(data[pivot] < data[pright])
    {
        swap(data[pivot], data[pright]);
        pivot = pright;
    }

    return pivot;
}
