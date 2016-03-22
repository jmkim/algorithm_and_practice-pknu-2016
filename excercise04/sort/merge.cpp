#include <stdio.h>
#include <string.h>

#include "merge.hpp"
#include "swap.hpp"

void merge(int *data, const int size_of_data)
{
    return merge(data, 0, size_of_data - 1);
}

void merge(int *data, const int start, const int end)
{
    int size = end - start + 1;

    if(size <= 2) /* base case */
    {
        if(data[start] > data[end]) swap(data[start], data[end]);
        return;
    }

    int s1 = start, e1 = s1 + size / 2;
    int s2 = e1 + 1, e2 = end;

    merge(data, s1, e1);
    merge(data, s2, e2);

    printf("========\nstart: %d | stop: %d\n", start, end);
    for(int i = start; i <= end; ++i) printf("data[%d] %d\n", i, data[i]);

    int temp[size] = {0, };
    int pt = 0;
    int p1 = s1, p2 = s2;

    while(p1 <= e1 && p2 <= e2)
    {
        printf("1 | s%d p%d e%d | s%d p%d e%d\n", s1, p1, e1, s2, p2, e2);
        while(p1 <= e1 && data[p1] <= data[p2])
        {
            temp[pt] = data[p1];
            printf("[%d/%d] %d <= %d [%d/%d]\n", p1, e1, data[p1], data[p2], p2, e2);
            pt++; p1++;
        }

        printf("2 | s%d p%d e%d | s%d p%d e%d\n", s1, p1, e1, s2, p2, e2);
        while(p2 <= e2 && data[p1] >= data[p2])
        {
            temp[pt] = data[p2];
            printf("[%d/%d] %d >= %d [%d/%d]\n", p1, e1, data[p1], data[p2], p2, e2);
            pt++; p2++;
        }
    }
    getchar();

    memcpy(data + start, temp, sizeof(int) * pt);
}
