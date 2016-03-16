#include <stdio.h>
#include <stdlib.h>

#define EMPTY   0
#define BLOCK   1
#define VISITED 2

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

bool is_horse_able_to_move(struct board *game, const int x, const int y)
{
    /* base case */
    if(x == game->x && y == game->y) return true;
    if(! is_empty(game, x, y)) return false;

    /* recursive case */
    game->board[x][y] = VISITED;
    if(is_empty(game, x - 1, y    , true) && (is_horse_able_to_move(game, x - 2, y - 1) || is_horse_able_to_move(game, x - 2, y + 1))) return true;
    if(is_empty(game, x    , y + 1, true) && (is_horse_able_to_move(game, x - 1, y + 2) || is_horse_able_to_move(game, x + 1, y + 2))) return true;
    if(is_empty(game, x + 1, y    , true) && (is_horse_able_to_move(game, x + 2, y + 1) || is_horse_able_to_move(game, x + 2, y - 1))) return true;
    if(is_empty(game, x    , y - 1, true) && (is_horse_able_to_move(game, x + 1, y - 2) || is_horse_able_to_move(game, x - 1, y - 2))) return true;

    return false;
}

int main(void)
{
    int startx, starty;
    struct board *game;
    
    game = make_board("resources/01input.txt", &startx, &starty);
    printf("%d\n", is_horse_able_to_move(game, startx, starty));

    free_board(game);
    return 0;
}
