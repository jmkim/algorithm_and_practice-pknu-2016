#include "../quicksort.hpp"
#include "../swap.hpp"

void quick(int *data, const int size_of_data)
{
    return quick(data, 0, size_of_data - 1);
}

void quick(int *data, const int start, const int end)
{
    /* Quicksort diagram: https://upload.wikimedia.org/wikipedia/commons/a/af/Quicksort-diagram.svg */

    if(start >= end) return;

    int pivot = partition(data, start, end);
    
    quick(data, start, pivot - 1);
    quick(data, pivot + 1, end);
}

int partition(int *data, const int start, const int end)
{
    int pleft = start,     /* Left to right */
        pivot = end;       /* Pivot */

    while(pleft != pivot)
    {
        while(pleft < pivot - 1 && data[pleft] <= data[pivot]) ++pleft;
        if(pleft == pivot - 1 && data[pleft] <= data[pivot]) break;

        {
            const int pvt = data[pivot];
            data[pivot] = data[pleft];
            data[pleft] = data[pivot - 1];
            data[pivot - 1] = pvt; /* Pivot moves left */
            --pivot;
        }
    }

    return pivot;
}
