#pragma once

#include "types.hpp"

class Chip8
{
public:
    Chip8();

    void emulateCycle();
    void loadGame(const char *game);

    bool renderFlag;

    u16 gfx[64 * 32];
    u8 keys[16];

private:
    u16 opcode;
    u16 pc;
    u16 I;

    u8 memory[4096];
    u8 V[16];

    u8 delayTimer;
    u8 soundTimer;

    u16 stack[16];
    u16 sp;
};
