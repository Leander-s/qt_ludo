#include "State.h"

namespace QtLudo {
LudoColor &operator++(LudoColor &color) {
  switch (color) {
  case LudoColor::red:
    return color = LudoColor::blue;
  case LudoColor::blue:
    return color = LudoColor::green;
  case LudoColor::green:
    return color = LudoColor::yellow;
  case LudoColor::yellow:
    return color = LudoColor::red;
  default:
    throw std::invalid_argument("This is not a Ludo color");
  }
}

uint8_t getPiece(LudoColor color, int index) {
  if (index > NUMBER_OF_PIECES_PER_PLAYER - 1) {
    throw std::invalid_argument("Piece index out of range");
  }
  switch (color) {
  case LudoColor::red:
    return index;
  case LudoColor::green:
    return index + greenOffset;
  case LudoColor::blue:
    return index + blueOffset;
  case LudoColor::yellow:
    return index + yellowOffset;
  }
  throw std::invalid_argument(
      "Color should be red, green, blue or yellow from enum LudoColor");
}
} // namespace QtLudo
