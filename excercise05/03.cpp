#include <stdio.h>

#include "../excercise04/make_random_data/make_random_data.hpp"
#include "../excercise04/sort/quicksort.hpp"

int quickselection(const int k, int *data, const int start, const int end)
{
    if(start >= end) return data[start];
    int pivot = partition(data, start, end);

    int p = pivot - start;
    if(p > k - 1) return quickselection(k, data, start, pivot - 1);
    if(p < k - 1) return quickselection(k - (p + 1), data, pivot + 1, end);
    return data[pivot];
}

int main(void)
{
    const int size = 100000;
    int *data = make_random_data(size);

    int k;
    printf("Enter k= ");
    scanf("%d", &k);

    if(k <= 0 || k > size)
    {
        printf("Error: Out of range.\n");
        return 1;
    }

    printf("%d\n", quickselection(k, data, 0, size - 1));

    free_random_data(data);
    return 0;
}
