#include <stdio.h>
#include <stdlib.h>

#define EMPTY   0
#define BLOCK   1
#define VISITED 2

struct board
{
    int size;    /* size of board */
    int **board; /* board */
};

int count_blob = 0;
int count_cell[10] = {0, };

struct board *make_board(const char *filename)
{
    struct board *blob = (struct board *)malloc(sizeof(struct board));

    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", &blob->size);
    blob->board = (int **)malloc(sizeof(int *) * blob->size);

    for(int row = 0; row < blob->size; row++)
    {
        blob->board[row] = (int *)malloc(sizeof(int) * blob->size);
        for(int col = 0; col < blob->size; col++)
        {
            int in;
            fscanf(fp, "%d", &in);
            blob->board[row][col] = ((in == 0) ? EMPTY : BLOCK);
        }
    }

    return blob;
}

void free_board(struct board *blob)
{
    for(int row = 0; row < blob->size; row++)
        free(blob->board[row]);
    free(blob->board);
    free(blob);
}

int get_count_cell(struct board *blob, const int x, const int y)
{
    /* base case */
    if(x < 0 || x >= blob->size || y < 0 || y >= blob->size) return 0;
    if(blob->board[x][y] != BLOCK) return 0;
    blob->board[x][y] = VISITED;

    /* recursive case */
    return 1
        + get_count_cell(blob, x - 1, y    )
        + get_count_cell(blob, x - 1, y + 1)
        + get_count_cell(blob, x    , y + 1)
        + get_count_cell(blob, x + 1, y + 1)
        + get_count_cell(blob, x + 1, y    )
        + get_count_cell(blob, x + 1, y - 1)
        + get_count_cell(blob, x    , y - 1)
        + get_count_cell(blob, x - 1, y - 1)
    ;
}

int get_count_blob(struct board *blob)
{
    for(int i = 0; i < blob->size; i++)
    {
        for(int j = 0; j < blob->size; j++)
            if(blob->board[i][j] == BLOCK)
                count_cell[count_blob++] = get_count_cell(blob, i, j);
    }
    return count_blob;
}

int main(void)
{
    struct board *blob = make_board("resources/03input.txt");
    printf("The number of blobs is %d.\n", get_count_blob(blob));

    for(int i = 0; i < count_blob; i++)
        printf("%d\n", count_cell[i]);

    free_board(blob);
    return 0;
}
