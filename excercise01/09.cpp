#include <stdio.h>

int binary_search(const int *nums, const int find, const int pos_a, const int pos_b)
{
    if(pos_b - pos_a <= 1) return pos_a;

    int mid = ((pos_b - pos_a) / 2) + pos_a;
    if(nums[mid] == find) return mid;

    if(nums[mid] < find)
        binary_search(nums, find, mid, pos_b);
    else
        binary_search(nums, find, 0, mid);
}

int main(void)
{
    int num[10] = { 0, 1, 4, 6, 7, 10, 14, 16, 16, 19 };
    printf("Result: %d\n", binary_search(num, 18, 0, 10));
}
