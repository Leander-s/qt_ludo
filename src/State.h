#pragma once
#include <QVector2D>
#include <iostream>
#include <stdexcept>
#include <stdint.h>

namespace QtLudo {
enum LudoColor { red, blue, yellow, green };

const char *printLudoColor(LudoColor color);

LudoColor operator++(LudoColor &color, int);

struct GameState {
  quint8 *positions;
  LudoColor toMove;
};
} // namespace QtLudo
