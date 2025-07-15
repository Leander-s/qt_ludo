#pragma once
#include "Map.h"
#include "State.h"

namespace QtLudo {
class Controller : public QObject {
  Q_OBJECT
public slots:
};

class Player {
public:
  Player(const LudoColor _color);
  const std::vector<bool> getPossibleMoves(const quint8 *positions,
                                           const quint8 roll,
                                           const MapConfig &config) const;
  bool moving;
  bool human;
  LudoColor color;
};

class HumanPlayer : public Player {
public:
  HumanPlayer(const LudoColor _color);
};

class AIPlayer : public Player {
public:
  AIPlayer(const LudoColor _color);
  virtual const quint8 decide(const quint8 *positions, const quint8 roll,
                              const MapConfig &config,
                              const quint8 playerOffset) const {
    return 0;
  }
};

class OneManArmy : public AIPlayer {
public:
  OneManArmy(const LudoColor _color) : AIPlayer(_color) {};
  const quint8 decide(const quint8 *positions, const quint8 roll,
                      const MapConfig &config,
                      const quint8 playerOffset) const override;
};

class YouNeverWalkAlone : public AIPlayer {
public:
  YouNeverWalkAlone(const LudoColor _color) : AIPlayer(_color) {};
  const quint8 decide(const quint8 *positions, const quint8 roll,
                      const MapConfig &config,
                      const quint8 playerOffset) const override;
};

class Pacifist : public AIPlayer {
public:
  Pacifist(const LudoColor _color) : AIPlayer(_color) {};
  const quint8 decide(const quint8 *positions, const quint8 roll,
                      const MapConfig &config,
                      const quint8 playerOffset) const override;
};

class Killer : public AIPlayer {
public:
  Killer(const LudoColor _color) : AIPlayer(_color) {};
  const quint8 decide(const quint8 *positions, const quint8 roll,
                      const MapConfig &config,
                      const quint8 playerOffset) const override;
};
} // namespace QtLudo
