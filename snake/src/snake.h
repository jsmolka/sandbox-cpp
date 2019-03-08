#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

#include <SDL.h>

#include "grid.h"
#include "key.h"
#include "point.h"
#include "vector.h"

typedef struct 
{
    Point *apple;
    Vector *body;
    Grid *grid;
} Snake;

Snake *snake_alloc(Grid *grid);
void snake_create_walls(Snake *this);
void snake_create_head(Snake *this);
void snake_create_apple(Snake *this);
void snake_move(Snake *this, Key key);
void snake_render(Snake *this, SDL_Window *window, SDL_Renderer *renderer);
bool snake_dead(Snake *this);
void snake_free(Snake *this);

#endif /* SNAKE_H */
