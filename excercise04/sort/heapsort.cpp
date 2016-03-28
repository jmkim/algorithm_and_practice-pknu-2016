#include "heapsort.hpp"
#include "heap.hpp"
#include "swap.hpp"

void heapsort(int *data, const int size_of_data)
{
    binary_max_heap(data, size_of_data - 1);

    do_heapsort(data, size_of_data - 1);
}

void do_heapsort(int *data, const int end)
{
    if(end <= 0) return;

    int k = 0;
    swap(data[k], data[end]); /* data[end] has been sorted and from now, should NOT touch */

    while(true)
    {
        if(2 * k + 2 < end) /* Have two child nodes */
        {
            if(data[k] < data[2 * k + 1] && data[2 * k + 1] >= data[2 * k + 2])
            {
                swap(data[k], data[2 * k + 1]);
                k = 2 * k + 1;
            }
            else if(data[k] < data[2 * k + 2])
            {
                swap(data[k], data[2 * k + 2]);
                k = 2 * k + 2;
            }
            else break;
        }
        else if(2 * k + 1 < end && data[k] < data[2 * k + 1]) /* Have one leaf node */
        {
            swap(data[k], data[2 * k + 1]);
            k = 2 * k + 1;
        }
        else break;
    }

    return do_heapsort(data, end - 1);
}
