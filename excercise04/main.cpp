#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "make_random_data/make_random_data.hpp"
#include "sort/merge.hpp"
#include "sort/selection.hpp"
#include "sort/insertion.hpp"
#include "sort/bubble.hpp"

#define MIN_SIZE    100
#define MAX_SIZE    100000
#define SIZE_STEP   10

int main(void)
{
    int *original = make_random_data(MAX_SIZE);

    for(int size_of_data = MIN_SIZE; size_of_data <= MAX_SIZE; size_of_data *= SIZE_STEP)
    {
        printf("SIZE OF DATA: %d\n", size_of_data);

        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            memcpy(data, original, size_of_data);

            clock_t before = clock();

            merge(data, size_of_data);

            clock_t after = clock();

            printf("%12s\t%lf\n", "Merge: ", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }
        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            memcpy(data, original, size_of_data);

            clock_t before = clock();

            selection(data, size_of_data);

            clock_t after = clock();

            printf("%12s\t%lf\n", "Selection: ", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }
        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            memcpy(data, original, size_of_data);

            clock_t before = clock();

            insertion(data, size_of_data);

            clock_t after = clock();

            printf("%12s%lf\n", "Insertion: ", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }
        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            memcpy(data, original, size_of_data);

            clock_t before = clock();

            bubble(data, size_of_data);

            clock_t after = clock();

            printf("%12s%lf\n", "Bubble: ", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }

        putchar('\n');
    }

    free_random_data(original);

    return 0;
}
