#include <stdio.h>

int count(const int *numbers, const int sum, const int index_a, const int index_b)
{
    /* base case */
    if(index_a >= index_b) return 0;

    /* recursive case */
    if(numbers[index_a] + numbers[index_b] == sum) /* match */
        return 1 + count(numbers, sum, index_a + 1, index_b - 1);
    else /* not match */
    {
        if(numbers[index_a] + numbers[index_b] < sum) return count(numbers, sum, index_a + 1, index_b);
        if(numbers[index_a] + numbers[index_b] > sum) return count(numbers, sum, index_a, index_b - 1);
    }
}

int count_of_two_sum(const int *numbers, const int number_count, const int sum)
{
    count(numbers, sum, 0, number_count - 1);
}

int main(void)
{
    printf("count of two sum\n");

    int sum, size_of_array;
    printf("Enter sum= "); scanf("%d", &sum);

    printf("Enter size_of_array= "); scanf("%d", &size_of_array);
    int array[size_of_array];
    printf("Enter in ascending order\n");
    for(int i = 0; i < size_of_array; i++)
    {
        printf("Enter array[%d]= ", i); scanf("%d", &array[i]);
    }

    printf("Result is %d\n", count_of_two_sum(array, size_of_array, sum));
    return 0;
}
