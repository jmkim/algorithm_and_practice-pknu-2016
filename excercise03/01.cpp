#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int n; /* Size of the board */
int *board;

/*
    Coordinates of the board

      1 2 3 4
    1 +------- y (cell)
    2 |
    3 |
    4 |
      x (line)

    x starts with 1; 0 is not used
    y starts with 1; 0 MEANS EMPTY

    board[0] is not used.
    board[1] = 3; means queen is at line 1, cell 3.
    board[1] = 0; means queen is not exist at line 1.
*/

bool is_setable_se(const int x, const int y)
{
    /* base case */
    if(x < 1 || x > n || y < 1 || y > n) return true;
    if(board[x - 1] == y) return false; /* Queen cannot be here */

    /* recursive case */
    return is_setable_se(x + 1, y + 1);
}

bool is_setable_s(const int x, const int y)
{
    if(x < 1 || x > n || y < 1 || y > n) return true;
    if(board[x - 1] == y) return false;
    return is_setable_s(x + 1, y);
}

bool is_setable_sw(const int x, const int y)
{
    if(x < 1 || x > n || y < 1 || y > n) return true;
    if(board[x - 1] == y) return false;
    return is_setable_sw(x + 1, y - 1);
}

bool is_setable(const int x, const int y)
{
    if(is_setable_se(x, y) && is_setable_s(x, y) && is_setable_sw(x, y)) return true;
    return false;
}

int b_set(const int x, const int y)
{
    /* set y to x */
    board[x - 1] = y;
    return 0; /* Do not effect the count calculation */
}

int b_unset(const int x)
{
    /* unset x */
    board[x - 1] = 0; /* 0 MEANS EMPTY */
    return 0;
}

int count_n_queens(const int x, const int y)
{
    /* base case */
    if(y < 1) return 0; /* y reached left side */

    /* recursive case */
    if(is_setable(x, y))
    {
        if(x - 1 < 1) /* x reached top side */
            return 1 + count_n_queens(x, y - 1); /* Queen can be here! */

        return b_set(x, y) + count_n_queens(x - 1, ::n) + b_unset(x) + count_n_queens(x, y - 1);
    }
    return count_n_queens(x, y - 1); /* Queen cannot be here */
}

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
