#include "Game.h"

namespace QtLudo {
Ludo::Ludo() {};
int Ludo::getPosition(ludo_color color, int index) {
    if(index > 3){
        throw std::invalid_argument("There are only 4 pieces per color");
    }
  switch (color) {
      case ludo_color::red:
          return positions[index];
      case ludo_color::green:
          return positions[index + 4];
      case ludo_color::blue:
          return positions[index + 8];
      case ludo_color::yellow:
          return positions[index + 12];
    }
}
} // namespace QtLudo
