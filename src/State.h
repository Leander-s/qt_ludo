#pragma once
#ifndef NDEBUG 
#define LOG(x) std::cout << x << std::endl
#endif

#include <QVector2D>
#include <QVector>
#include <iostream>
#include <stdexcept>
#include <stdint.h>

namespace QtLudo {
// Ludo Color
enum LudoColor { red, blue, green, yellow};

const char *printLudoColor(LudoColor color);

LudoColor operator++(LudoColor &color, int);
// Ludo Color

struct GameState {
  quint8 *positions;
  quint8 toMoveIndex;
};
} // namespace QtLudo
