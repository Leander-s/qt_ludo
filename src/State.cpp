#include "State.h"

namespace QtLudo {
LudoColor operator++(LudoColor &color, int) {
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

const char* printLudoColor(LudoColor color){
    switch(color){
        case LudoColor::red:
            return "Red";
        case LudoColor::blue:
            return "Blue";
        case LudoColor::green:
            return "Green";
        case LudoColor::yellow:
            return "Yellow";
    }
    return 0;
}

uint8_t getPiece(LudoColor color, int index) {
  if (index > 4 - 1) {
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

uint8_t getOffset(LudoColor color){
    switch(color){
        case LudoColor::red: return 0;
        case LudoColor::green: return greenOffset;
        case LudoColor::blue: return blueOffset;
        case LudoColor::yellow: return yellowOffset;
    }
    return 0;
}
} // namespace QtLudo
