#pragma once
#include <QVector2D>
#include <iostream>
#include <stdexcept>
#include <stdint.h>

namespace QtLudo {
// Ludo Color
enum LudoColor { red, blue, yellow, green };

const char *printLudoColor(LudoColor color);

LudoColor operator++(LudoColor &color, int);
// Ludo Color

struct GameState {
  quint8* positions;
  quint8 toMoveIndex;
};
} // namespace QtLudo
