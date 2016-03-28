#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "make_random_data/make_random_data.hpp"
#include "sort/heapsort.hpp"
#include "sort/quicksort.hpp"
#include "sort/merge_sort.hpp"
#include "sort/selection_sort.hpp"
#include "sort/insertion_sort.hpp"
#include "sort/bubble_sort.hpp"

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
            memcpy(data, original, sizeof(int) * size_of_data);

            clock_t before = clock();

            heapsort(data, size_of_data);

            clock_t after = clock();

            printf("Heapsort:\t\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }
        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            memcpy(data, original, sizeof(int) * size_of_data);

            clock_t before = clock();

            quicksort(data, size_of_data);

            clock_t after = clock();

            printf("Quicksort:\t\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }
        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            memcpy(data, original, sizeof(int) * size_of_data);

            clock_t before = clock();

            merge_sort(data, size_of_data);

            clock_t after = clock();

            printf("Merge sort:\t\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }
        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            memcpy(data, original, sizeof(int) * size_of_data);

            clock_t before = clock();

            insertion_sort(data, size_of_data);

            clock_t after = clock();

            printf("Insertion sort:\t\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }
        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            memcpy(data, original, sizeof(int) * size_of_data);

            clock_t before = clock();

            selection_sort(data, size_of_data);

            clock_t after = clock();

            printf("Selection sort:\t\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }
        {
            int *data = (int *)malloc(sizeof(int) * size_of_data);
            memcpy(data, original, sizeof(int) * size_of_data);

            clock_t before = clock();

            bubble_sort(data, size_of_data);

            clock_t after = clock();

            printf("Bubble sort:\t\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
            free(data);
        }

        putchar('\n');
    }

    free_random_data(original);

    return 0;
}
