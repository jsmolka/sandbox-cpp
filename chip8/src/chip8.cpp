#include "chip8.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#define VX V[(opcode & 0x0F00) >> 8]
#define VY V[(opcode & 0x00F0) >> 4]
#define VF V[0xF]

constexpr u8 chip8_fontset[80] =
{
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8()
{
    renderFlag = false;

    opcode = 0;
    pc     = 0x200;
    I      = 0;
    sp     = 0;

    delayTimer = 0;
    soundTimer = 0;

    std::memset(memory, 0, sizeof(memory));
    std::memset(V,      0, sizeof(V));
    std::memset(gfx,    0, sizeof(gfx));
    std::memset(stack,  0, sizeof(stack));
    std::memset(keys,   0, sizeof(keys));

    for (int i = 0; i < 80; ++i)
        memory[i] = chip8_fontset[i];
}

void Chip8::emulateCycle()
{
    // Fetch opcode
    opcode = memory[pc] << 8 | memory[pc + 1];

    // Decode opcode
    switch (opcode & 0xF000)
    {
    case 0x0000:
        switch (opcode & 0x000F)
        {
        case 0x000: // 0x00E0: Clears the screen.
            std::memset(gfx, 0, sizeof(gfx));
            renderFlag = true;
            pc += 2;
            break;

        case 0x00E: // 0x00EE: Returns from a subroutine.
            pc = stack[--sp];
            pc += 2;
            break;

        default:
            std::cout << "Unknown opcode: " << std::hex << opcode << std::endl;
        }
        break;

    case 0x1000: // 0x1NNN: Jumps to address NNN.
        pc = opcode & 0x0FFF;
        break;

    case 0x2000: // 0x2NNN: Calls subroutine at NNN.
        stack[sp++] = pc;
        pc = opcode & 0x0FFF;
        break;

    case 0x3000: // 0x3XNN: Skips the next instruction if VX equals NN.
        pc += VX == (opcode & 0x00FF) ? 4 : 2;
        break;

    case 0x4000: // 0x4XNN: Skips the next instruction if VX doesn't equal NN.
        pc += VX != (opcode & 0x00FF) ? 4 : 2;
        break;

    case 0x5000: // 0x5XY0: Skips the next instruction if VX equals VY.
        pc += VX == VY ? 4 : 2;
        break;

    case 0x6000: // 0x6XNN: Sets VX to NN.
        VX = opcode & 0x00FF;
        pc += 2;
        break;

    case 0x7000: // 0x7XNN: Adds NN to VX. Carry flag is not changed.
        VX += opcode & 0x00FF;
        pc += 2;
        break;

    case 0x8000:
        switch (opcode & 0x000F)
        {
        case 0x0000: // 0x8XY0: Sets VX to the value of VY.
            VX = VY;
            pc += 2;
            break;

        case 0x0001: // 0x8XY1: Sets VX to VX or VY.
            VX |= VY;
            pc += 2;
            break;

        case 0x0002: // 0x8XY2: Sets VX to VX and VY.
            VX &= VY;
            pc += 2;
            break;
        
        case 0x0003: // 0x8XY1: Sets VX xor VX or VY.
            VX ^= VY;
            pc += 2;
            break;

        case 0x0004: // 0x8XY4: Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
            VF = VX + VY > 255 ? 1 : 0;
            VX += VY;
            pc += 2;
            break;

        case 0x0005: // 0x8XY5: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
            VF = VY > VX ? 0 : 1;
            VX -= VY;
            pc += 2;
            break;

        case 0x0006: // 0x8XY6: Stores the least significant bit of VX in VF and then shifts VX to the right by 1.
            VF = VX & 0x1;
            VX >>= 1;
            pc += 2;
            break;

        case 0x0007: // 0x8XY7: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
            VF = VX > VY ? 0 : 1;
            VX = VY - VX;
            pc += 2;
            break;

        case 0x0008: // 0x8XYE: Stores the most significant bit of VX in VF and then shifts VX to the left by 1.
            VF = VX >> 7;
            VX <<= 1;
            pc += 2;
            break;

        default:
            std::cout << "Unknown opcode: " << std::hex << opcode << std::endl;
        }
        break;

    case 0x9000: // 0x9XY0: Skips the next instruction if VX doesn't equal VY.
        pc += VX != VY ? 4 : 2;
        break;

    case 0xA000: // 0xANNN: Sets I to the adress NNN
        I = opcode & 0x0FFF;
        pc += 2;
        break;

    case 0xB000: // 0xBNNN: Jumps to the address NNN plus V0.
        pc = (opcode & 0x0FFF) + V[0];
        break;

    case 0xC000: // 0xCXNN: Sets VX to the result of a bitwise and operation on a random number (0 to 255) and NN.
        VX = (rand() % 0xFF) & (opcode & 0x00FF);
        pc += 2;
        break;

    case 0xD000: // 0xDXYN
        // Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each
        // row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after
        // the execution of this instruction. As described above, VF is set to 1 if any screen pixels are
        // flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen.
        VF = 0;
        for (u8 row = 0; row < (opcode & 0x000F); ++row)
        {
            u8 pixels = memory[I + row];
            for (u8 col = 0; col < 8; ++col)
            {
                if ((pixels & (0x80 >> col)) != 0)
                {
                    u16 &pixel = gfx[(VX + col + ((VY + row) * 64))];
                    if (pixel == 1)
                        VF = 1;

                    pixel ^= 1;
                }
            }
        }
        renderFlag = true;
        pc += 2;
        break;

    case 0xE000:
        switch (opcode & 0x00FF)
        {
        case 0x009E: // 0xEX9E: Skips the next instruction if the key stored in VX is pressed.
            pc += keys[VX] != 0 ? 4 : 2;
            break;

        case 0x00A1: // 0xEXA1: Skips the next instruction if the key stored in VX isn't pressed.
            pc += keys[VX] == 0 ? 4 : 2;
            break;
        }
        break;

    case 0xF000:
        switch (opcode & 0x00FF)
        {
        case 0x0007: // 0xFX07: Sets VX to the value of the delay timer.
            VX = delayTimer;
            pc += 2;
            break;

        case 0x000A: // 0xFX0A: A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event)
        {
            bool keyPress = false;

            for(u8 i = 0; i < 16; ++i)
            {
                if(keys[i] != 0)
                {
                    VX = i;
                    keyPress = true;
                }
            }

            if(!keyPress)
                return;

            pc += 2;
            break;
        }

        case 0x0015: // 0xFX15: Sets the delay timer to VX.
            delayTimer = VX;
            pc += 2;
            break;

        case 0x0018: // 0xFX18: Sets the sound timer to VX.
            soundTimer = VX;
            pc += 2;
            break;

        case 0x001E: // 0xFX1E: Adds VX to I. VF is set to 1 when range overflow and 0 when there isn't.
            VF = VX + I > 0xFFF ? 1 : 0;
            I += VX;
            pc += 2;
            break;

        case 0x0029: // 0xFX29: Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
            I = VX * 0x5;
            pc += 2;
            break;

        case 0x0033: // 0xFX33
            // Stores the binary-coded decimal representation of VX, with the most significant of three digits
            // at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2.
            // (In other words, take the decimal representation of VX, place the hundreds digit in memory at
            // location in I, the tens digit at location I+1, and the ones digit at location I+2.)
            memory[I] = VX / 100;
            memory[I + 1] = (VX / 10) % 10;
            memory[I + 2] = (VX % 100) % 10;
            pc += 2;
            break;

        case 0x0055: // 0xFX55
            // Stores V0 to VX (including VX) in memory starting at address I. The offset from I is increased by 1
            // for each value written, but I itself is left unmodified.
            for (u8 i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
                memory[I + i] = V[i];

            I += ((opcode & 0x0F00) >> 8) + 1;
            pc += 2;
            break;

        case 0x0065: // 0xFX65
            // Fills V0 to VX (including VX) with values from memory starting at address I. The offset from I is
            // increased by 1 for each value written, but I itself is left unmodified.
            for (u8 i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
                V[i] = memory[I + i];

            I += ((opcode & 0x0F00) >> 8) + 1;
            pc += 2;
            break;

        default:
            std::cout << "Unknown opcode: " << std::hex << opcode << std::endl;
        }
        break;

    default:
        std::cout << "Unknown opcode: " << std::hex << opcode << std::endl;
    }

    if (delayTimer > 0)
        --delayTimer;

    if (soundTimer > 0)
        --soundTimer;
}

void Chip8::loadGame(const char *game)
{
    std::ifstream file(game, std::ios::binary);

    file.unsetf(std::ios::skipws);

    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<u8> buffer;
    buffer.reserve(size);
    buffer.insert(buffer.begin(), std::istream_iterator<u8>(file), std::istream_iterator<u8>());

    for (unsigned int i = 0; i < buffer.size(); ++i)
        memory[i + 512] = buffer[i];
}
