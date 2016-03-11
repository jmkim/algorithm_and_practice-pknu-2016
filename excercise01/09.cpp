#include <stdio.h>

int binary_search(const int *numbers, const int find, const int index_a, const int index_b)
{
    if(index_a == index_b) return index_a;
    if(index_b - index_a / 2 == 0) return index_a;
    if(numbers[(index_b - index_a) / 2] == find) return (index_b - index_a) / 2;

    if(numbers[(index_b - index_a) / 2] < find) return binary_search(numbers, find, 0, (index_b - index_a) / 2);
    if(numbers[(index_b - index_a) / 2] > find) return binary_search(numbers, find, (index_b - index_b) / 2, index_b);
}

int main(void)
{
    int num[10] = { 0, 1, 4, 6, 7, 10, 14, 16, 18, 19 };
    printf("Result: %d\n", binary_search(num, 9, 0, 10));
}
