#include <stdio.h>

int calc_area(int step)
{
    /* base case */
    if(step == 1) return 1;

    /* recursive case */
    return step + calc_area(step - 1);
}

int calc_volume(int step)
{
    /* base case */
    if(step == 1) return 1;

    /* recursive case */
    return calc_area(step) + calc_volume(step - 1);
}

int main(void)
{
    printf("count the ball of tetrahedron\n");

    int step;
    printf("Enter step= "); scanf("%d", &step);

    printf("Result is %d\n", calc_volume(step));
    return 0;
}
