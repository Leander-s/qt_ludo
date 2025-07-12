#pragma once
#include "State.h"
#include <QObject>

namespace QtLudo {
class Controller : public QObject {
  Q_OBJECT
public slots:
};

enum PlayerType { human, AI };
class Player {
public:
  std::vector<bool> getPossibleMoves(uint8_t *positions, uint8_t roll,
                                     MapConfig config, uint8_t playerOffset);
  bool moving;
  bool human;
  LudoColor color;
};

class HumanPlayer : Player {

private:
  Controller controller;
};

class AIPlayer : public Player {
public:
  virtual uint8_t decide(uint8_t *positions, uint8_t roll, MapConfig config,
                         uint8_t playerOffset);
};

class OneManArmy : AIPlayer {
public:
  uint8_t decide(uint8_t *positions, uint8_t roll, MapConfig config,
                 uint8_t playerOffset) override;
};

class YouNeverWalkAlone : AIPlayer {
public:
  uint8_t decide(uint8_t *positions, uint8_t roll, MapConfig config,
                 uint8_t playerOffset) override;
};

class Pacifist : AIPlayer {
public:
  uint8_t decide(uint8_t *positions, uint8_t roll, MapConfig config,
                 uint8_t playerOffset) override;
};

class Killer : AIPlayer {
public:
  uint8_t decide(uint8_t *positions, uint8_t roll, MapConfig config,
                 uint8_t playerOffset) override;
};
} // namespace QtLudo
