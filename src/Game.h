#pragma once
#include "ModelUtil.h"
#include "Players.h"
#include "GLGameObject.h"
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include "State.h"
#include <stdlib.h>
#include <time.h>


namespace QtLudo {
// This should be in a config file
class Ludo {
public:
  Ludo();
  void start();
  void update();
  uint8_t roll(uint32_t seed);
  LudoColor startingRoll();

  uint8_t getPosition(LudoColor color, int index);

  GameState *state;

private:

};
} // namespace QtLudo
