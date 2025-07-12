#pragma once
#include <QVector2D>
#include <iostream>
#include <stdexcept>
#include <stdint.h>

namespace QtLudo {
const std::array<QVector2D, 66> positionMappings = {
    QVector2D(-6.0f, -6.0f), QVector2D(-3.0f, -6.0f), QVector2D(-6.0f, -3.0f),
    QVector2D(-3.0f, -3.0f), QVector2D(-7.0f, -1.0f), QVector2D(-6.0f, -1.0f),
    QVector2D(-5.0f, -1.0f), QVector2D(-4.0f, -1.0f), QVector2D(-3.0f, -1.0f),
    QVector2D(-2.0f, -1.0f), QVector2D(-1.0f, -1.0f), QVector2D(-1.0f, -2.0f),
    QVector2D(-1.0f, -3.0f), QVector2D(-1.0f, -4.0f), QVector2D(-1.0f, -5.0f),
    QVector2D(-1.0f, -6.0f), QVector2D(-1.0f, -7.0f), QVector2D(0.0f, -7.0f),
    QVector2D(1.0f, -7.0f),  QVector2D(1.0f, -6.0f),  QVector2D(1.0f, -5.0f),
    QVector2D(1.0f, -4.0f),  QVector2D(1.0f, -3.0f),  QVector2D(1.0f, -2.0f),
    QVector2D(1.0f, -1.0f),  QVector2D(2.0f, -1.0f),  QVector2D(3.0f, -1.0f),
    QVector2D(4.0f, -1.0f),  QVector2D(5.0f, -1.0f),  QVector2D(6.0f, -1.0f),
    QVector2D(7.0f, -1.0f),  QVector2D(7.0f, 0.0f),   QVector2D(7.0f, 1.0f),
    QVector2D(6.0f, 1.0f),   QVector2D(5.0f, 1.0f),   QVector2D(4.0f, 1.0f),
    QVector2D(3.0f, 1.0f),   QVector2D(2.0f, 1.0f),   QVector2D(1.0f, 1.0f),
    QVector2D(1.0f, 2.0f),   QVector2D(1.0f, 3.0f),   QVector2D(1.0f, 4.0f),
    QVector2D(1.0f, 5.0f),   QVector2D(1.0f, 6.0f),   QVector2D(1.0f, 7.0f),
    QVector2D(0.0f, 7.0f),   QVector2D(-1.0f, 7.0f),  QVector2D(-1.0f, 6.0f),
    QVector2D(-1.0f, 5.0f),  QVector2D(-1.0f, 4.0f),  QVector2D(-1.0f, 3.0f),
    QVector2D(-1.0f, 2.0f),  QVector2D(-1.0f, 1.0f),  QVector2D(-2.0f, 1.0f),
    QVector2D(-3.0f, 1.0f),  QVector2D(-4.0f, 1.0f),  QVector2D(-5.0f, 1.0f),
    QVector2D(-6.0f, 1.0f),  QVector2D(-7.0f, 1.0f),  QVector2D(-7.0f, 0.0f),
    QVector2D(-6.0f, 0.0f),  QVector2D(-5.0f, 0.0f),  QVector2D(-4.0f, 0.0f),
    QVector2D(-3.0f, 0.0f),  QVector2D(-2.0f, 0.0f),  QVector2D(-1.0f, 0.0f),
};
// Offsets by color
// This needs to be fixed but I don't want to think about it right now
const uint8_t redOffset = 0;
const uint8_t greenOffset = redOffset + 4;
const uint8_t blueOffset = greenOffset + 4;
const uint8_t yellowOffset = blueOffset + 4;

enum LudoColor { red, blue, yellow, green };

const char *printLudoColor(LudoColor color);

LudoColor operator++(LudoColor &color, int);

uint8_t getPiece(LudoColor color, int index);

uint8_t getOffset(LudoColor color);

struct MapConfig {
  uint8_t numberOfPlayers;
  uint8_t numberOfPiecesPerPlayer;
  uint8_t numberOfPieces;
  uint8_t lengthOfPath;
};

struct GameState {
  uint8_t *positions;
  LudoColor toMove;
};
} // namespace QtLudo
