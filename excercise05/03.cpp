#include <stdio.h>

#include "../excercise04/make_random_data/make_random_data.hpp"
#include "../excercise04/sort/quicksort.hpp"

int get_index_smallest(const int k, int *data, const int start, const int end)
{
    if(k < 0 || k > end) return -1; /* Base case */
    int p = partition(data, start, end);

    if(k == 0) return data[start];
    else if(p - start == k) return data[p];
    else if(p - start > k) return get_index_smallest(k, data, start, p - 1);
    else return get_index_smallest(k - p - 1, data, p + 1, end);
}

int main(void)
{
    int k;
    printf("Enter k= ");
    scanf("%d", &k);

    const int size = 100000;
    int *data = make_random_data(size);
    printf("%d\n", get_index_smallest(k, data, 0, size - 1));

    free_random_data(data);
    return 0;
}
