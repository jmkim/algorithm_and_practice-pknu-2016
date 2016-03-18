#include <stdio.h>
#include <stdlib.h>

int *list;
int size;
int sum;

void trim_out_of_range(void)
{
    for(int i = size - 1; i >= 0; i--)
        if(list[i] > sum)
        {
            for(int j = i; j < size; j++) list[j] = list[j + 1];
            size--;
        }
}

int count_sum(const int idx, const int sum = 0)
{
    if(idx < 0 && sum == ::sum) return 1;
    if(idx < 0) return 0;

    return count_sum(idx - 1, sum + list[idx]) + count_sum(idx - 1, sum);
}

int main(void)
{
    printf("Enter n= "); scanf("%d", &size);

    list = (int *)malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++)
    {
        printf("Enter list[%d]= ", i); scanf("%d", &list[i]);
    }

    printf("Enter k= "); scanf("%d", &sum);

    trim_out_of_range();
    printf("Result: %d\n", count_sum(size - 1));

    free(list);

    return 0;
}
