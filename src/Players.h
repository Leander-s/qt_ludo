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
  Player(LudoColor _color);
  std::vector<bool> getPossibleMoves(uint8_t *positions, uint8_t roll,
                                     MapConfig config);
  bool moving;
  bool human;
  LudoColor color;
};

class HumanPlayer : public Player {
public:
  HumanPlayer(LudoColor _color);
};

class AIPlayer : public Player {
public:
  AIPlayer(LudoColor _color);
  virtual uint8_t decide(uint8_t *positions, uint8_t roll, MapConfig config,
                         uint8_t playerOffset) {
    return 0;
  }
};

class OneManArmy : public AIPlayer {
public:
  OneManArmy(LudoColor _color) : AIPlayer(_color) {};
  uint8_t decide(uint8_t *positions, uint8_t roll, MapConfig config,
                 uint8_t playerOffset) override;
};

class YouNeverWalkAlone : public AIPlayer {
public:
  YouNeverWalkAlone(LudoColor _color) : AIPlayer(_color) {};
  uint8_t decide(uint8_t *positions, uint8_t roll, MapConfig config,
                 uint8_t playerOffset) override;
};

class Pacifist : public AIPlayer {
public:
  Pacifist(LudoColor _color) : AIPlayer(_color) {};
  uint8_t decide(uint8_t *positions, uint8_t roll, MapConfig config,
                 uint8_t playerOffset) override;
};

class Killer : public AIPlayer {
public:
  Killer(LudoColor _color) : AIPlayer(_color) {};
  uint8_t decide(uint8_t *positions, uint8_t roll, MapConfig config,
                 uint8_t playerOffset) override;
};
} // namespace QtLudo
