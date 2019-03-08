#ifndef GRID_H
#define GRID_H

typedef struct
{
    int **grid;
    int rows;
    int cols;
} Grid;

enum GridValue
{
    GRID_FREE = 0,
    GRID_WALL = 1,
    GRID_APPLE = 2,
    GRID_HEAD = 3,
    GRID_BODY = 4
};

Grid *grid_alloc(int rows, int cols);
void grid_set(Grid *this, int row, int col, int val);
int grid_get(Grid *this, int row, int col);
void grid_free(Grid *this);

#endif /* GRID_H */
