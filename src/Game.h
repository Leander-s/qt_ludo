#pragma once
#include "GLGameObject.h"
#include "Map.h"
#include "ModelUtil.h"
#include "Players.h"
#include "State.h"
#include <memory>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <stdlib.h>
#include <time.h>

namespace QtLudo {
// This should be in a config file
class Ludo {
public:
  Ludo(const Map *_map);
  Ludo();
  ~Ludo();
  void start();
  const quint8 findMove(const quint8 playerIndex, const quint8 dieRoll);
  void applyMove(const quint8 playerIndex, const quint8 figure, const quint8 dieRoll);
  const quint8 roll(const quint32 seed);
  const quint8 startingRoll();

  const MapConfig config;
  const Map *map;
  GameState state;
  std::vector<Player> players;
  bool humanMove;
};
} // namespace QtLudo
