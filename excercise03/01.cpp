#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DIR_SE  3
#define DIR_S   4
#define DIR_SW  5

bool is_able_to_set(const int x, const int y, const int dir = -1);
int shift_left(const int x, const int y);
int shift_up(const int x, const int y);

int n;
int *board;

int main(void)
{
    for(n = 1; n <= 15; n++)
    {
        board = (int *)malloc(sizeof(int) * n);
        memset(board, 0, sizeof(int) * n);

        printf("N(%d) Result=%d\n", n, shift_left(n, n));
        free(board);
    }

    return 0;
}

bool is_able_to_set(const int x, const int y, const int dir)
{
    /* base case */
    if(x < 1 || x > n || y < 1 || y > n) return true;
    if(board[x - 1] == y) return false; /* queen is exist */

    /* recursive case */
    switch(dir)
    {
    case DIR_SE: return is_able_to_set(x + 1, y + 1, DIR_SE);
    case DIR_S : return is_able_to_set(x + 1, y    , DIR_S );
    case DIR_SW: return is_able_to_set(x + 1, y - 1, DIR_SW);
    default: /* re-call with a direction */
        if(
            is_able_to_set(x, y, DIR_SE) &&
            is_able_to_set(x, y, DIR_S ) &&
            is_able_to_set(x, y, DIR_SW)
        ) return true;
        return false;
    }
}

int shift_left(const int x, const int y)
{
    if(y < 1) return 0;

    int rc = 0;
    if(is_able_to_set(x, y))
    {
        board[x - 1] = y;
        rc += shift_up(x, ::n);
        board[x - 1] = 0;
    }
    rc += shift_left(x, y - 1);
    return rc;
}

int shift_up(const int x, const int y)
{
    if(x - 1 < 1 && is_able_to_set(x - 1, y)) return 1;
    if(x - 1 < 1) return 0;

    return shift_left(x - 1, y);
}
