#include <stdio.h>

int count(const int *numbers_a, const int *numbers_b, const int size_a, const int size_b, const int index_a, const int index_b)
{
    /* base case */
    if(index_a >= size_a || index_b >= size_b) return 0;

    /* recursive case */
    if(numbers_a[index_a] == numbers_b[index_b]) /* match */
        return 1 + count(numbers_a, numbers_b, size_a, size_b, index_a + 1, index_b + 1);
    else /* not match */
    {
        if(numbers_a[index_a] < numbers_b[index_b]) return count(numbers_a, numbers_b, size_a, size_b, index_a + 1, index_b);
        if(numbers_a[index_a] > numbers_b[index_b]) return count(numbers_a, numbers_b, size_a, size_b, index_a, index_b + 1);
    }
}

int count_of_two_sum(const int *numbers_a, const int *numbers_b, const int number_count_a, const int number_count_b)
{
    count(numbers_a, numbers_b, number_count_a, number_count_b, 0, 0);
}

int main(void)
{
    printf("count of two sum\n");

    int size_of_array_a, size_of_array_b;

    printf("Enter size_of_array_a= "); scanf("%d", &size_of_array_a);
    int array_a[size_of_array_a];
    printf("Enter in ascending order\n");
    for(int i = 0; i < size_of_array_a; i++)
    {
        printf("Enter array_a[%d]= ", i); scanf("%d", &array_a[i]);
    }

    printf("Enter size_of_array_b= "); scanf("%d", &size_of_array_b);
    int array_b[size_of_array_b];
    printf("Enter in ascending order\n");
    for(int i = 0; i < size_of_array_b; i++)
    {
        printf("Enter array_b[%d]= ", i); scanf("%d", &array_b[i]);
    }

    printf("Result is %d\n", count_of_two_sum(array_a, array_b, size_of_array_a, size_of_array_b));
    return 0;
}
