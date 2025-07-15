#include "State.h"

namespace QtLudo {
LudoColor operator++(LudoColor &color, int) {
  switch (color) {
  case LudoColor::red:
    return color = LudoColor::blue;
  case LudoColor::blue:
    return color = LudoColor::yellow;
  case LudoColor::yellow:
    return color = LudoColor::green;
  case LudoColor::green:
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
} // namespace QtLudo
