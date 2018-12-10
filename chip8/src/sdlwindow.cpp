#include "sdlwindow.hpp"

SdlWindow::SdlWindow()
    : quit(false)
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Chip8",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        320,
        SDL_WINDOW_OPENGL
    );
    renderer = SDL_CreateRenderer(window, -1, 0);
}

SdlWindow::~SdlWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

bool SdlWindow::isQuit() const
{
    return quit;
}

int SdlWindow::lastKey() const
{
    return key;
}

void SdlWindow::draw(u16 gfx[])
{
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    for (int x = 0; x < 32; ++x)
    {
        for (int y = 0; y < 64; ++y)
        {
            u16 p = gfx[y + (x * 64)];
            u8 c = p == 1 ? 255 : 0;

            SDL_Rect rect = {y * 10, x * 10, 10, 10};
            SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, c, c, c));
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
    SDL_UpdateWindowSurface(window);
}

void SdlWindow::processEvents(u8 keys[])
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
            updateKey(keys, event.key.keysym.sym, 1);

        if (event.type == SDL_KEYUP)
            updateKey(keys, event.key.keysym.sym, 0);

        if (event.type == SDL_QUIT)
             quit = true;
    }
}

void SdlWindow::updateKey(u8 keys[], SDL_Keycode key, int value)
{
    switch (key)
    {
    case SDLK_1: keys[0x1] = value; break;
    case SDLK_2: keys[0x2] = value; break;
    case SDLK_3: keys[0x3] = value; break;
    case SDLK_4: keys[0xC] = value; break;
    case SDLK_q: keys[0x4] = value; break;
    case SDLK_w: keys[0x5] = value; break;
    case SDLK_e: keys[0x6] = value; break;
    case SDLK_r: keys[0xD] = value; break;
    case SDLK_a: keys[0x7] = value; break;
    case SDLK_s: keys[0x8] = value; break;
    case SDLK_d: keys[0x9] = value; break;
    case SDLK_f: keys[0xE] = value; break;
    case SDLK_z: keys[0xA] = value; break;
    case SDLK_x: keys[0x0] = value; break;
    case SDLK_c: keys[0xB] = value; break;
    case SDLK_v: keys[0xF] = value; break;
    }
}
