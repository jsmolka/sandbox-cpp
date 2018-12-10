#include <cstdlib>
#include <ctime>
#include <cstdio>

#include "chip8.hpp"
#include "sdlwindow.hpp"

int main(int argc, char *argv[])
{
    srand(time(0));

    if (argc != 2)
    {
        printf("Usage: %s game", argv[0]);
        return 0;
    }

    SdlWindow window;

    Chip8 chip;
    chip.loadGame(argv[1]);

    while (!window.isQuit())
    {
        chip.emulateCycle();

        if (chip.renderFlag)
            window.draw(chip.gfx);

        window.processEvents(chip.keys);
    }
    return 0;
}
