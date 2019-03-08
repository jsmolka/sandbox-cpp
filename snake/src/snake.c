#include "snake.h"

#include <stdlib.h>

#include "const.h"
#include "util.h"

Snake *snake_alloc(Grid *grid)
{
    Snake *this = (Snake *)malloc(sizeof(Snake));
    this->apple = point_alloc(0, 0);
    this->body = vector_alloc(1, (Deallocator)point_free);
    this->grid = grid;

    return this;
}

void snake_create_walls(Snake *this)
{
    for (int c = 0; c < this->grid->cols; ++c)
    {
        grid_set(this->grid, 0, c, GRID_WALL);
        grid_set(this->grid, this->grid->rows - 1, c, GRID_WALL);
    }
    for (int r = 0; r < this->grid->rows; ++r)
    {
        grid_set(this->grid, r, 0, GRID_WALL);
        grid_set(this->grid, r, this->grid->cols - 1, GRID_WALL);
    }
}

void snake_create_head(Snake *this)
{
    Point *head = point_alloc(0, 0);
    head->r = randint(1, this->grid->rows - 2);
    head->c = randint(1, this->grid->cols - 2);

    vector_push(this->body, head);

    grid_set(this->grid, head->r, head->c, GRID_HEAD);
}

void snake_create_apple(Snake *this)
{
    Point *apple = this->apple;

    if (grid_get(this->grid, apple->r, apple->c) == GRID_APPLE)
        grid_set(this->grid, apple->r, apple->c, GRID_FREE);

    do
    {
        apple->r = randint(1, this->grid->rows - 2);
        apple->c = randint(1, this->grid->cols - 2);
    }
    while (grid_get(this->grid, apple->r, apple->c) != GRID_FREE);
    
    grid_set(this->grid, apple->r, apple->c, GRID_APPLE);
}

void snake_move(Snake *this, Key key)
{
    if (key == KEY_NONE)
        return;

    Point *head = (Point *)vector_first(this->body);
    if (point_equal(head, this->apple))
    {
        Point *last = (Point *)vector_last(this->body);
        vector_push(this->body, point_alloc(last->r, last->c));
        snake_create_apple(this);
    }

    Point prev;
    for (size_t i = 0; i < vector_len(this->body); ++i)
    {
        Point *point = (Point *)vector_get(this->body, i);
        if (i == 0)
        {
            point_assign(&prev, point);
            point_move(point, key);

            grid_set(this->grid, point->r, point->c, GRID_HEAD);
            grid_set(this->grid, prev.r, prev.c, vector_len(this->body) == 1 ? GRID_FREE : GRID_BODY);

            continue;
        }
        
        if (point_equal(&prev, point))
            break;

        point_swap(&prev, point);

        if (i == vector_len(this->body) - 1)
        {
            if (grid_get(this->grid, prev.r, prev.c) != GRID_HEAD)
                grid_set(this->grid, prev.r, prev.c, GRID_FREE);
        }
    }
}

void snake_render(Snake *this, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    for (int r = 0; r < this->grid->rows; ++r)
    {
        for (int c = 0; c < this->grid->cols; ++c)
        {
            SDL_Rect rect = {c * scale, r * scale, scale, scale};

            switch (grid_get(this->grid, r, c))
            {
            case GRID_FREE: SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0, 0, 0)); break;
            case GRID_WALL: SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 255, 255)); break;
            case GRID_APPLE: SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 0, 0)); break;
            case GRID_HEAD: SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0, 255, 0)); break;
            case GRID_BODY: SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0, 160, 0)); break;
            }
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
    SDL_UpdateWindowSurface(window);
}

bool snake_dead(Snake *this)
{
    Point *head = (Point *)vector_first(this->body);

    for (size_t i = 1; i < vector_len(this->body); ++i)
    {
        Point *body = (Point *)vector_get(this->body, i);
        if (point_equal(body, head))
            return true;
    }

    return head->r == 0 || head->r == this->grid->rows - 1
        || head->c == 0 || head->c == this->grid->cols - 1;
}

void snake_free(Snake *this)
{
    point_free(this->apple);
    vector_free(this->body);
    free(this);
}
