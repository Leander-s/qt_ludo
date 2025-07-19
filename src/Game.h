#pragma once
#include "GLGameObject.h"
#include "Map.h"
#include "ModelUtil.h"
#include "Players.h"
#include "State.h"
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include <QRandomGenerator>

namespace QtLudo {
// This should be in a config file
class Ludo {
public:
  Ludo(const Map *_map);
  ~Ludo();
  void start();
  const quint8 findMove(const quint8 playerIndex, const quint8 dieRoll);
  const quint8 applyMove(const quint8 playerIndex, const quint8 playerFigure,
                         const quint8 dieRoll);
  const quint8 roll();
  const quint8 startingRoll();
  const quint8 getFigure(const quint8 playerIndex,
                         const quint8 playerFigure) const;

  const quint8 getPosition(const quint8 figure) const;
  const quint8 getToMove() const;

  const MapConfig config;
  const Map *map;
  std::vector<Player> players;
  bool humanMove;
  QRandomGenerator rng;

  GameState state;
};
} // namespace QtLudo
