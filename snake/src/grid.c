#include "grid.h"

#include <stdlib.h>

Grid *grid_alloc(int rows, int cols)
{
    Grid *this = (Grid *)malloc(sizeof(Grid));
    this->grid = (int **)malloc(rows * sizeof(int *));
    this->rows = rows;
    this->cols = cols;

    for (int r = 0; r < rows; ++r)
    {
        this->grid[r] = (int *)malloc(cols * sizeof(int));
        for (int c = 0; c < cols; ++c)
            this->grid[r][c] = 0;
    }
    return this;
}

void grid_set(Grid *this, int row, int col, int val)
{
    this->grid[row][col] = val;
}

int grid_get(Grid *this, int row, int col)
{
    return this->grid[row][col];
}

void grid_free(Grid *this)
{
    for (int r = 0; r < this->rows; ++r)
        free(this->grid[r]);

    free(this->grid);
    free(this);
}
