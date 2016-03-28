#include <string.h> /* memcpy() */

#include "merge_sort.hpp"

void merge_sort(int *data, const int size_of_data)
{
    return merge(data, 0, size_of_data - 1);
}

void merge(int *data, const int start, const int end)
{
    int size = end - start + 1;
    if(size <= 1) return; /* base case */

    /* divide */
    int s1 = start,     e1 = s1 + size / 2 - 1,
        s2 = e1 + 1,    e2 = end;
    merge(data, s1, e1);
    merge(data, s2, e2);

    /* conquer */
    int temp[size] = {0, };
    int pt = 0, p1 = s1, p2 = s2;
    while(p1 <= e1 && p2 <= e2)
    {
        while(p1 <= e1 && data[p1] <= data[p2]) temp[pt++] = data[p1++];
        while(p2 <= e2 && data[p1] >= data[p2]) temp[pt++] = data[p2++];
    }
    while(p1 <= e1) temp[pt++] = data[p1++];
    while(p2 <= e2) temp[pt++] = data[p2++];

    /* copy the sorted data */
    memcpy(data + start, temp, sizeof(int) * size);
}
