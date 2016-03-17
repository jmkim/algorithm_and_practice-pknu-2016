#include <stdio.h>
#include <stdlib.h>

int *list;
int size;
int sum;

int main(void)
{
    size = 9;
    sum = 15;
    list = (int *)malloc(sizeof(int) * size);

    list[0] = 1;
    list[1] = 5;
    list[2] = 8;
    list[3] = 3;
    list[4] = 7;
    list[5] = 12;
    list[6] = 11;
    list[7] = 2;
    list[8] = 6;

    func(size - 1);

    free(list);

    return 0;
}
