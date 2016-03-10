#include <stdio.h>

int combination(const int n, const int r)
{
    if(r < 0 || n < 0 || r > n) return -1; /* out of range */

    if(n == 0) /* base case */
        return 0;
    else if(r == 0 || r == n)
        return 1;
    else if(r == 1)
        return n;
    else /* recursive case */
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
