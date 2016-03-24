#include <string.h> /* memcpy() */
#include <stdlib.h> /* rand() */

#include "quick.hpp"
#include "swap.hpp"

void quick(int *data, const int size_of_data)
{
    return quick(data, 0, size_of_data - 1);
}

void quick(int *data, const int start, const int end)
{
    int size = end - start + 1;
    if(size <= 1) return; /* Base case */

    /* Conquer */
    int pivot = end; /* Set pivot */

    int lss[size] = {0, }; /* Memory which stores less than data[pivot] */
    int gtr[size] = {0, }; /*                     greater               */
    int pos_lss = 0, pos_gtr = 0;

    for(int pos = start; pos <= end; ++pos)
    {
        if(pos == pivot) continue; /* Ignore pivot */

        if(data[pos] < data[pivot])
            lss[pos_lss++] = data[pos];
        else
            gtr[pos_gtr++] = data[pos];
    }

    /* Copy the sorted data */
    data[start + pos_lss] = data[pivot];
    memcpy(data + start, lss, sizeof(int) * pos_lss);
    memcpy(data + start + pos_lss + 1, gtr, sizeof(int) * pos_gtr);

    /* Divide */
    quick(data, start, start + pos_lss - 1);
    quick(data, start + pos_lss + 1, end);
}
