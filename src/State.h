#pragma once
#ifndef NDEBUG 
#define LOG(x) std::cout << x << std::endl
#endif

// std
#include <iostream>
#include <stdexcept>
#include <stdint.h>

// Qt
#include <QVector2D>
#include <QVector>

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
