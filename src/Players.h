#pragma once

namespace QtLudo {
enum ludo_color { red, blue, yellow, green };
class Player {
public:
  ludo_color color;
  int decide();
};
class Human : Player {
  int decide();
};
class AI : Player {
public:
  int strategy;
  int decide(int positions[16]);
};
} // namespace QtLudo
