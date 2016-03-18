#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DIR_SE  3
#define DIR_S   4
#define DIR_SW  5

bool is_able_to_set(const int x, const int y, const int dir = -1);
int count_n_queens(const int x, const int y);

int n;
int *board;

int main(void)
{
    for(n = 1; n <= 15; n++)
    {
        board = (int *)malloc(sizeof(int) * n);
        memset(board, 0, sizeof(int) * n);

        printf("N(%d) Result=%d\n", n, count_n_queens(n, n));
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

int b_add(const int x, const int y)
{
    board[x - 1] = y; /* 0 MEANS EMPTY */
    return 0;
}

int b_rm(const int x)
{
    board[x - 1] = 0; /* 0 MEANS EMPTY */
    return 0;
}

int count_n_queens(const int x, const int y)
{
    /* base case */
    if(y < 1) return 0;

    /* recursive case */
    if(is_able_to_set(x, y))
    {
        if(x - 1 >= 1)                  return count_n_queens(x, y - 1) + b_add(x, y) + count_n_queens(x - 1, ::n) + b_rm(x);
        if(is_able_to_set(x - 1, ::n))  return count_n_queens(x, y - 1) + 1;
    }
    return count_n_queens(x, y - 1);
}
