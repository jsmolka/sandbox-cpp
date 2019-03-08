#ifndef POINT_H
#define POINT_H

#include <stdbool.h>

#include "key.h"

typedef struct
{
    int r;
    int c;
} Point;

Point *point_alloc(int row, int col);
void point_move(Point *this, Key key);
void point_free(Point *this);

bool point_equal(Point *lhs, Point *rhs);
void point_assign(Point *dst, Point *src);
void point_swap(Point *lhs, Point *rhs);

#endif /* POINT_H */
