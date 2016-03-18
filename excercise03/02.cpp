#include <stdio.h>
#include <stdlib.h>

void trim_out_of_range(void);
int shift_right(const int idx, const int sum = 0);
int shift_down(const int idx, const int sum = 0);

int *list;
int size;
int sum;

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
    printf("Result: %d\n", shift_right(size - 1));

    free(list);

    return 0;
}

void trim_out_of_range(void)
{
    for(int i = size - 1; i >= 0; i--)
        if(list[i] > sum)
        {
            for(int j = i; j < size; j++) list[j] = list[j + 1];
            size--;
        }
}

int shift_right(const int idx, const int sum)
{
    if(idx < 0 && sum == ::sum) return 1;
    if(idx < 0) return 0;

    return shift_right(idx - 1, sum + list[idx]) + shift_down(idx, sum);
}

int shift_down(const int idx, const int sum)
{
    if(idx - 1 < 0 && sum == ::sum) return 1;
    if(idx - 1 < 0) return 0;

    return shift_right(idx - 1, sum);
}
