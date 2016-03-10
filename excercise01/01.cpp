#include <stdio.h>

int sum_of_odd_number(const int n)
{
    /* base case */
    if(n < 2) return n; /* calc(n-2) must be greater than zero */
    if((n % 2) == 0) return sum_of_odd_number(n - 1);

    /* recursive case */
    return n + sum_of_odd_number(n - 2);
}

int main(void)
{
    printf("sum of the odd number\n");
    printf("max value: n\n");

    int n;
    printf("Enter n= "); scanf("%d", &n);

    printf("Result is %d\n", sum_of_odd_number(n));
    return 0;
}
