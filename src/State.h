#pragma once
#include <stdint.h>
#include <stdexcept>

#define NUMBER_OF_PLAYERS 4
#define NUMBER_OF_PIECES_PER_PLAYER 4
#define NUMBER_OF_PIECES (NUMBER_OF_PIECES_PER_PLAYER * NUMBER_OF_PLAYERS)

namespace QtLudo{
// Offsets by color
const uint8_t redOffset = 0;
const uint8_t greenOffset = redOffset + NUMBER_OF_PIECES_PER_PLAYER;
const uint8_t blueOffset = greenOffset + NUMBER_OF_PIECES_PER_PLAYER;
const uint8_t yellowOffset = blueOffset + NUMBER_OF_PIECES_PER_PLAYER;

enum LudoColor { red, blue, yellow, green };

LudoColor &operator++(LudoColor& color);

uint8_t getPiece(LudoColor color, int index);

struct GameState {
  uint8_t positions[NUMBER_OF_PIECES];
  LudoColor toMove;
};
}
