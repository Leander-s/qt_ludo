#pragma once
#include "GLGameObject.h"
#include "ModelUtil.h"
#include "Players.h"
#include "State.h"
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <array>
#include <stdlib.h>
#include <time.h>

namespace QtLudo {
// This should be in a config file
class Ludo {
public:
  Ludo(MapConfig newConfig);
  ~Ludo();
  void start();
  uint8_t findMove(Player *player, uint8_t dieRoll);
  void applyMove(uint8_t totalPiece, uint8_t dieRoll);
  uint8_t roll(uint32_t seed);
  LudoColor startingRoll();

  uint8_t getPosition(LudoColor color, int index);

  GameState *state;
  MapConfig config;

  bool humanMove;

  std::vector<Player*> players;
  int getPlayer(LudoColor color);
};
} // namespace QtLudo
