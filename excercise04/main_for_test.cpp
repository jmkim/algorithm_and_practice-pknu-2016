#include <stdio.h>
#include <stdlib.h>
#include "make_random_data/make_random_data.hpp"
#include "sort/quicksort.hpp"
#include "sort/merge_sort.hpp"
#include "sort/selection_sort.hpp"
#include "sort/insertion_sort.hpp"
#include "sort/bubble_sort.hpp"

#define SORT    quicksort
#define SIZE    20

int main(void)
{
    int *data = make_random_data(SIZE, 99);

    for(int i = 0; i < SIZE; ++i) printf("%d\n", data[i]);
    putchar('\n');

    SORT(data, SIZE);

    for(int i = 0; i < SIZE; ++i) printf("%d\n", data[i]);

    free_random_data(data);

    return 0;
}
