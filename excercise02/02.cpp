#include <stdio.h>
#include <stdlib.h>

#define EMPTY   0
#define BLOCK   1
#define VISITED 2

#define DIR_N   0
#define DIR_E   1
#define DIR_S   2
#define DIR_W   3

struct board
{
    int size;    /* size of game board */
    int x, y;    /* destination */
    int **board; /* game board */
};

struct board *make_board(const char *filename, int *startx, int *starty)
{
    struct board *game = (struct board *)malloc(sizeof(struct board));

    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d %d %d %d %d", &game->size, startx, starty, &game->x, &game->y);
    game->board = (int **)malloc(sizeof(int *) * game->size);

    for(int row = 0; row < game->size; row++)
    {
        game->board[row] = (int *)malloc(sizeof(int) * game->size);
        for(int col = 0; col < game->size; col++)
        {
            int in;
            fscanf(fp, "%d", &in);
            game->board[row][col] = ((in == 0) ? EMPTY : BLOCK);
        }
    }

    return game;
}

void free_board(struct board *game)
{
    for(int row = 0; row < game->size; row++)
        free(game->board[row]);
    free(game->board);
    free(game);
}

bool is_empty(struct board *game, const int x, const int y, const bool is_able_to_jump = false)
{
    if(x < 0 || x >= game->size || y < 0 || y >= game->size) return false;
    if(game->board[x][y] == EMPTY || is_able_to_jump && game->board[x][y] == VISITED) return true;
    return false;
}

int count_direction_first_block(struct board *game, const int dir, const int x, const int y)
{
    switch(dir)
    {               /* base case is inside in recursive case is_empty() */
    case DIR_N: { if(is_empty(game, x - 1, y    )) return count_direction_first_block(game, dir, x - 1, y    ) + 1; break; }
    case DIR_E: { if(is_empty(game, x    , y + 1)) return count_direction_first_block(game, dir, x    , y + 1) + 1; break; }
    case DIR_S: { if(is_empty(game, x + 1, y    )) return count_direction_first_block(game, dir, x + 1, y    ) + 1; break; }
    case DIR_W: { if(is_empty(game, x    , y - 1)) return count_direction_first_block(game, dir, x    , y - 1) + 1; break; }
    }
    return 0;
}

bool is_canon_able_to_move(struct board *game, const int x, const int y);
bool is_canon_able_to_move_in_range(struct board *game, const int dir, const int x, const int y, const int n)
{
    /* base case */
    if(n == 0) return false;
    if(x == game->x && y == game->y) return true;
    switch(dir)
    {
    case DIR_N: { if(is_canon_able_to_move(game, x - n, y    )) return true; break; }
    case DIR_E: { if(is_canon_able_to_move(game, x    , y + n)) return true; break; }
    case DIR_S: { if(is_canon_able_to_move(game, x + n, y    )) return true; break; }
    case DIR_W: { if(is_canon_able_to_move(game, x    , y - n)) return true; break; }
    }

    /* recursive case */
    return is_canon_able_to_move_in_range(game, dir, x, y, n - 1);
}

bool is_canon_able_to_move(struct board *game, const int x, const int y)
{
    /* base case */
    if(x == game->x && y == game->y) return true;
    if(! is_empty(game, x, y, true)) return false;

    /* recursive case */
    game->board[x][y] = VISITED;

    if(is_canon_able_to_move_in_range(game, DIR_N, x - count_direction_first_block(game, DIR_N, x, y) - 2, y, count_direction_first_block(game, DIR_N, x - count_direction_first_block(game, DIR_N, x, y) - 1, y))) return true;
    if(is_canon_able_to_move_in_range(game, DIR_E, x, y + count_direction_first_block(game, DIR_E, x, y) + 2, count_direction_first_block(game, DIR_E, x, y + count_direction_first_block(game, DIR_E, x, y) + 1))) return true;
    if(is_canon_able_to_move_in_range(game, DIR_S, x + count_direction_first_block(game, DIR_S, x, y) + 2, y, count_direction_first_block(game, DIR_S, x + count_direction_first_block(game, DIR_S, x, y) + 1, y))) return true;
    if(is_canon_able_to_move_in_range(game, DIR_W, x, y - count_direction_first_block(game, DIR_W, x, y) - 2, count_direction_first_block(game, DIR_W, x, y - count_direction_first_block(game, DIR_W, x, y) - 1))) return true;

    return false;
}

int main(void)
{
    int startx, starty;
    struct board *game;
    game = make_board("resources/01input.txt", &startx, &starty);

    printf("%d\n", is_canon_able_to_move(game, startx, starty));

    free_board(game);
    return 0;
}
