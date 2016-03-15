#include <stdio.h>
#include <stdlib.h>

#define EMPTY   0
#define BLOCK   1
#define VISITED 2

struct board
{
    int size;
    int x, y;
    int **board;
};

struct board game;
int x, y;

void make_board(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d %d %d %d %d", &game.size, &x, &y, &game.x, &game.y);
    game.board = (int **)malloc(sizeof(int *) * game.size);

    for(int row = 0; row < game.size; row++)
    {
        game.board[row] = (int *)malloc(sizeof(int) * game.size);
        for(int col = 0; col < game.size; col++)
        {
            int in;
            fscanf(fp, "%d", &in);
            game.board[row][col] = ((in == 0) ? EMPTY : BLOCK);
        }
    }
}

void free_board(void)
{
    for(int row = 0; row < game.size; row++)
        free(game.board[row]);
    free(game.board);
}

bool is_empty(const int x, const int y, const bool flag = false)
{
    if(x < 0 || x >= game.size || y < 0 || y >= game.size) return false;
    if(game.board[x][y] == EMPTY || flag && game.board[x][y] == VISITED) return true;
    return false;
}

bool is_horse_able_to_move(const int x, const int y)
{
    /* base case */
    if(x == game.x && y == game.y) return true;
    if(! is_empty(x, y)) return false;

    /* recursive case */
    game.board[x][y] = VISITED;
    if(is_empty(x - 1, y    , true) && (is_horse_able_to_move(x - 2, y - 1) || is_horse_able_to_move(x - 2, y + 1))) return true;
    if(is_empty(x    , y + 1, true) && (is_horse_able_to_move(x - 1, y + 2) || is_horse_able_to_move(x + 1, y + 2))) return true;
    if(is_empty(x + 1, y    , true) && (is_horse_able_to_move(x + 2, y + 1) || is_horse_able_to_move(x + 2, y - 1))) return true;
    if(is_empty(x    , y - 1, true) && (is_horse_able_to_move(x + 1, y - 2) || is_horse_able_to_move(x - 1, y - 2))) return true;

    return false;
}

int main(void)
{
    make_board("resources/01input.txt");
    printf("%d\n", is_horse_able_to_move(0, 0));
    free_board();
    return 0;
}
