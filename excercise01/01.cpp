#include <stdio.h>

int calc(const int n)
{
    if(n < 2) /* base case: calc(n-2) must be greater than zero */
        return n;
    else if((n % 2) == 0)
        return calc(n - 1);
    else /* recursive case */
        return n + calc(n - 2);
}

int main(void)
{
    printf("sum of the odd number\n");
    printf("max value: n\n");

    int n;
    printf("Enter n= "); scanf("%d", &n);

    printf("Result is %d\n", calc(n));
    return 0;
}
