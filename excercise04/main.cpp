#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "make_random_data/make_random_data.hpp"
#include "sort/merge.hpp"
#include "sort/selection.hpp"
#include "sort/insertion.hpp"
#include "sort/bubble.hpp"

int main(void)
{
    for(int size_of_data = 100; size_of_data == 100000; size_of_data *= 10)
    {
        int *original = make_random_data(size_of_data);
        printf("SIZE OF DATA: %d\n", size_of_data);

        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            clock_t before = clock();

            merge(original, data);

            clock_t after = clock();
            printf("Merge:\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }
        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            clock_t before = clock();

            selection(original, data);

            clock_t after = clock();
            printf("Selection:\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }
        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            clock_t before = clock();

            insertion(original, data);

            clock_t after = clock();
            printf("Insertion:\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }
        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            clock_t before = clock();

            bubble(original, data);

            clock_t after = clock();
            printf("Bubble:\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }

        putchar('\n');
    }

    return 0;
}
