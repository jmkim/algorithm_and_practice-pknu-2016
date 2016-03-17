#include <stdio.h>
#include <stdbool.h>

#define DIR_N   0
#define DIR_NE  1
#define DIR_E   2
#define DIR_SE  3
#define DIR_S   4
#define DIR_SW  5
#define DIR_W   6
#define DIR_NW  7

const int n = 8;
int board[n] = {0, };

bool is_able_to_set(const int x, const int y, const int dir = -1)
{
    /* base case */
    if(x < 1 || x > n || y < 1 || y > n) return true;
    if(board[x - 1] == y) return false; /* queen is exist */

    /* recursive case */
    switch(dir)
    {
    //case DIR_N : return is_able_to_set(x - 1, y    , DIR_N );
    //case DIR_NE: return is_able_to_set(x - 1, y + 1, DIR_NE);
    //case DIR_E : return is_able_to_set(x    , y + 1, DIR_E );
    case DIR_SE: return is_able_to_set(x + 1, y + 1, DIR_SE);
    case DIR_S : return is_able_to_set(x + 1, y    , DIR_S );
    case DIR_SW: return is_able_to_set(x + 1, y - 1, DIR_SW);
    //case DIR_W : return is_able_to_set(x   1, y - 1, DIR_W );
    //case DIR_NW: return is_able_to_set(x - 1, y - 1, DIR_NW);
    default: /* re-call with a direction */
        if(
            //is_able_to_set(x, y, DIR_N )
            //is_able_to_set(x, y, DIR_NE)
            //is_able_to_set(x, y, DIR_E )
            is_able_to_set(x, y, DIR_SE) &&
            is_able_to_set(x, y, DIR_S ) &&
            is_able_to_set(x, y, DIR_SW)
            //is_able_to_set(x, y, DIR_W )
            //is_able_to_set(x, y, DIR_NW)
        ) return true;
        return false;
    }
}

int shift_up(const int x, const int y);
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

int main(void)
{
    int count = shift_left(n, n);
    printf("%d\n", count);

    return 0;
}
