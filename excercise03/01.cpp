#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int n; /* size of the board */
int *board; /* 0 MEANS EMPTY */

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

bool is_able_to_set_se(const int x, const int y)
{
    /* base case */
    if(x < 1 || x > n || y < 1 || y > n) return true;
    if(board[x - 1] == y) return false; /* queen is exist */

    /* recursive case */
    return is_able_to_set_se(x + 1, y + 1);
}

bool is_able_to_set_s(const int x, const int y)
{
    /* base case */
    if(x < 1 || x > n || y < 1 || y > n) return true;
    if(board[x - 1] == y) return false; /* queen is exist */

    /* recursive case */
    return is_able_to_set_s(x + 1, y);
}

bool is_able_to_set_sw(const int x, const int y)
{
    /* base case */
    if(x < 1 || x > n || y < 1 || y > n) return true;
    if(board[x - 1] == y) return false; /* queen is exist */

    /* recursive case */
    return is_able_to_set_sw(x + 1, y - 1);
}

bool is_able_to_set(const int x, const int y)
{
    if(is_able_to_set_se(x, y) && is_able_to_set_s(x, y) && is_able_to_set_sw(x, y)) return true;
    return false;
}

int b_set(const int x, const int y)
{
    /* set y to x */
    board[x - 1] = y;
    return 0;
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
    if(is_able_to_set(x, y))
    {
        if(x - 1 >= 1)                  return count_n_queens(x, y - 1) + b_set(x, y) + count_n_queens(x - 1, ::n) + b_unset(x);
        if(is_able_to_set(x - 1, ::n))  return count_n_queens(x, y - 1) + 1; /* x reached top side; Queen can be here! */
    }
    return count_n_queens(x, y - 1);
}

int main(void)
{
    for(n = 1; n <= 15; n++)
    {
        board = (int *)malloc(sizeof(int) * n);
        memset(board, 0, sizeof(int) * n); /* 0 MEANS EMPTY */

        printf("N(%d) Result=%d\n", n, count_n_queens(n, n));
        free(board);
    }

    return 0;
}
