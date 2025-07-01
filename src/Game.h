#pragma once
#include <stdexcept>
#include "Players.h"

namespace QtLudo {
class Ludo {
public:
  Ludo();
  void update();

  int getPosition(ludo_color color, int index);

  int positions[16];

  // Offsets by color
  int red = 0;
  int green = 4;
  int blue = 8;
  int yellow = 12;
};
} // namespace QtLudo
