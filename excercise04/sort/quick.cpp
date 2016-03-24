#include <stdio.h>

#include "quick.hpp"
#include "swap.hpp"

void quick(int *data, const int size_of_data)
{
    return quick(data, 0, size_of_data - 1);
}

void quick(int *data, const int start, const int end)
{
    int size = end - start + 1;

#ifdef TESTLAYOUT
    printf("START %d : END %d : PIVOT %d\n", start, end, data[end]);
    for(int i = start; i <= end; ++i) printf(" %2d  ", data[i]);
    printf("\n");
#endif

    if(start >= end) return; /* Base case */

    /* Conquer */
    int pivot = end; /* Set pivot */

    int ps = start, pe = end - 1;
    while(ps < pe)
    {
        while(ps < pe && data[ps] < data[pivot]) ++ps;
        while(ps < pe && data[pe] >= data[pivot]) --pe;

#ifdef TESTLAYOUT
        for(int i = start; i <= end; ++i)
        {
            if(i == ps && i == pe)
                printf("(%2d) ", data[i]);
            else if(i == ps || i == pe)
                printf("[%2d] ", data[i]);
            else
                printf(" %2d  ", data[i]);
        }
        printf("  (%d, %d)\n", ps, pe);
#endif

        if(ps < pe) swap(data[ps], data[pe]);
    }

    if(data[pe] > data[pivot]) swap(data[pe], data[pivot]);

#ifdef TESTLAYOUT
    for(int i = start; i <= end; ++i) printf(" %2d  ", data[i]);
    printf("\n");
#endif

    /* Divide */
    quick(data, start, pe);
    quick(data, pe + 1, end);
}
