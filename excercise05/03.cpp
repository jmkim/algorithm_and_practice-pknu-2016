#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../excercise04/make_random_data/make_random_data.hpp"
#include "../excercise04/sort/quicksort.hpp"

int quickselect(const int k, int *data, const int start, const int end)
{
    if(start >= end) return data[start];
    int pivot = partition(data, start, end);

    int p = pivot - start;
    if(p > k - 1) return quickselect(k, data, start, pivot - 1);
    if(p < k - 1) return quickselect(k - (p + 1), data, pivot + 1, end);
    return data[pivot];
}

int main(void)
{
    const int size_of_data = 100000;
    int *original = make_random_data(size_of_data);

    int k;
    printf("Enter k= ");
    scanf("%d", &k);

    if(k <= 0 || k > size_of_data)
    {
        printf("Error: Out of range.\n");
        return 1;
    }

    {
        int data[size_of_data];
        memcpy(data, original, sizeof(int) * size_of_data);

        clock_t before = clock();

        printf("Result: %d\n", quickselect(k, data, 0, size_of_data - 1));

        clock_t after = clock();

        printf("Quickselection:\t\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
    }
    {
        int data[size_of_data];
        memcpy(data, original, sizeof(int) * size_of_data);

        clock_t before = clock();

        quick(data, size_of_data);
        printf("Result: %d\n", data[k - 1]);

        clock_t after = clock();

        printf("Quicksort:\t\t%lf\n", (double)(after - before)/CLOCKS_PER_SEC);
    }

    free_random_data(original);
    return 0;
}
