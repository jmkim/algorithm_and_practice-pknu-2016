#include <stdio.h>
#include <stdlib.h>
#include "make_random_data/make_random_data.hpp"
#include "sort/merge.hpp"
#include "sort/quick.hpp"
#include "sort/selection.hpp"
#include "sort/insertion.hpp"
#include "sort/bubble.hpp"

#define SORT    quick
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
