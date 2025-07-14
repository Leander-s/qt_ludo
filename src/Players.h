#pragma once
#include "State.h"
#include "Map.h"

namespace QtLudo {
class Controller : public QObject {
  Q_OBJECT
public slots:
};

enum PlayerType { human, AI };
class Player {
public:
  Player(LudoColor _color);
  std::vector<bool> getPossibleMoves(quint8 *positions, quint8 roll,
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
  virtual quint8 decide(quint8 *positions, quint8 roll, const MapConfig &config,
                         quint8 playerOffset) {
    return 0;
  }
};

class OneManArmy : public AIPlayer {
public:
  OneManArmy(LudoColor _color) : AIPlayer(_color) {};
  quint8 decide(quint8 *positions, quint8 roll, MapConfig config,
                 quint8 playerOffset) override;
};

class YouNeverWalkAlone : public AIPlayer {
public:
  YouNeverWalkAlone(LudoColor _color) : AIPlayer(_color) {};
  quint8 decide(quint8 *positions, quint8 roll, MapConfig config,
                 quint8 playerOffset) override;
};

class Pacifist : public AIPlayer {
public:
  Pacifist(LudoColor _color) : AIPlayer(_color) {};
  quint8 decide(quint8 *positions, quint8 roll, MapConfig config,
                 quint8 playerOffset) override;
};

class Killer : public AIPlayer {
public:
  Killer(LudoColor _color) : AIPlayer(_color) {};
  quint8 decide(quint8 *positions, quint8 roll, MapConfig config,
                 quint8 playerOffset) override;
};
} // namespace QtLudo
