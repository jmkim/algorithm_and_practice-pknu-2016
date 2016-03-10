#include <stdio.h>

int fibonacci(const int n)
{
    if(n == 0 || n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void)
{
    printf("Fibonacci calulator\n");

    int n;
    printf("Enter n= "); scanf("%d", &n);

    printf("Result is %d\n", fibonacci(n));
    return 0;
}
