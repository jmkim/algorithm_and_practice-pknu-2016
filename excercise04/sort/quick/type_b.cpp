#include "../quick.hpp"
#include "../swap.hpp"

void quick(int *data, const int size_of_data)
{
    return quick(data, 0, size_of_data - 1);
}

void quick(int *data, const int start, const int end)
{
    int size = end - start + 1;

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

    int ps = start,
        pe = end - 1;

    while(ps != pe)
    {
        while(ps < pe && data[ps] <= data[pivot]) ++ps;
        while(ps < pe && data[pe] >= data[pivot]) --pe;

        if(ps < pe) swap(data[ps], data[pe]);
    }

    if(data[pivot] < data[pe])
    {
        swap(data[pivot], data[pe]);
        pivot = pe;
    }

    return pivot;
}
