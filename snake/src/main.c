#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>

#include "const.h"
#include "grid.h"
#include "key.h"
#include "snake.h"
#include "util.h"

static void process_events(Key *key)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_w: *key = KEY_W; break;
            case SDLK_a: *key = KEY_A; break;
            case SDLK_s: *key = KEY_S; break;
            case SDLK_d: *key = KEY_D; break;
            case SDLK_ESCAPE: *key = KEY_ESC; break;
            }
        }

        if (event.type == SDL_QUIT)
            *key = KEY_ESC;
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if (argc != 3) 
    {
        printf("Usage: %s [rows] [cols]\n", argv[0]);
        return 0;
    }

    const int rows = MAX(atoi(argv[1]), 2) + 2;
    const int cols = MAX(atoi(argv[2]), 2) + 2;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Snake",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        cols * scale,
        rows * scale,
        0
    );
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Grid *grid = grid_alloc(rows, cols);
    Snake *snake = snake_alloc(grid);

    snake_create_walls(snake);
    snake_create_head(snake);
    snake_create_apple(snake);

    Key key = KEY_NONE;
    while (key != KEY_ESC)
    {
        process_events(&key);

        snake_move(snake, key);
        snake_render(snake, window, renderer);
        
        if (snake_dead(snake))
            break;

        SDL_Delay(125);
    }

    snake_free(snake);
    grid_free(grid);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
