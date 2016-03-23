#include <stdlib.h>
#include <time.h>

#include "make_random_data.hpp"

int *make_random_data(const int size)
{
    return make_random_data(size, RAND_MAX);
}

int *make_random_data(const int size, const int max)
{
    srand(time(NULL)); /* Set a seed */

    int *data = (int *)malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++)
        data[i] = rand() % (max + 1);

    return data;
}

void free_random_data(int *data)
{
    free(data);
}

