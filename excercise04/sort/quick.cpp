#include <stdio.h>
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

    int ps = start, pe = end - 1;
    while(ps < pe)
    {
        while(ps < pe && data[ps] < data[pivot]) ++ps;
        while(ps < pe && data[pe] >= data[pivot]) --pe;

        if(ps < pe) swap(data[ps], data[pe]);
    }

    if(data[pe] > data[pivot]) swap(data[pe], data[pivot]);

    /* Divide */
    quick(data, start, pe);
    quick(data, pe + 1, end);
}
