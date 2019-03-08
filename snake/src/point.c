#include "point.h"

#include <stdlib.h>

Point *point_alloc(int row, int col)
{
    Point *this = (Point *)malloc(sizeof(Point));
    this->r = row;
    this->c = col;

    return this;
}

void point_move(Point *this, Key key)
{
    switch (key)
    {
    case KEY_NONE: break;
    case KEY_W: this->r--; break;
    case KEY_A: this->c--; break;
    case KEY_S: this->r++; break;
    case KEY_D: this->c++; break;
    case KEY_ESC: break;
    }
}

void point_free(Point *this)
{
    free(this);
}

bool point_equal(Point *lhs, Point *rhs)
{
    return lhs->r == rhs->r && lhs->c == rhs->c;
}

void point_assign(Point *dst, Point *src)
{
    dst->r = src->r;
    dst->c = src->c;
}

void point_swap(Point *lhs, Point *rhs)
{
    Point temp;
    point_assign(&temp, lhs);
    point_assign(lhs, rhs);
    point_assign(rhs, &temp);
}
