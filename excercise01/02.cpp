#include <stdio.h>

int combination(const int n, const int r)
{
    /* base case */
    if(r < 0 || n < 0 || r > n) return 0;
    if(r == 0) return 1;

    /* recursive case */
    return combination(n - 1, r) + combination(n - 1, r - 1);
}

int main(void)
{
    printf("combination calculator\n");
    printf("nCr (0 <= r <= n)\n");

    int n, r;
    printf("Enter n= "); scanf("%d", &n);
    printf("Enter r= "); scanf("%d", &r);

    printf("Result is %d\n", combination(n, r));
    return 0;
}
