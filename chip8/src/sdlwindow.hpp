#ifndef SDLWINDOW_HPP
#define SDLWINDOW_HPP

#include <SDL.h>

#include "types.hpp"

class SdlWindow
{
public:
    SdlWindow();
    ~SdlWindow();

    bool isQuit() const;
    int lastKey() const;

    void draw(u16 gfx[]);
    void processEvents(u8 keys[]);

private:
    void updateKey(u8 keys[], SDL_Keycode key, int value);

    SDL_Window *window;
    SDL_Renderer *renderer;
    bool quit;
    int key;
};

#endif // SDLWINDOW_HPP
