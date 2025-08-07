#pragma once

// std
#include <memory>
#include <stdlib.h>

// Mine
#include <GLGameObject.h>
#include <Players.h>
#include <util.h>

// Qt
#include <QRandomGenerator>

namespace QtLudo {
const quint8 noMovesPossibleCode = 255;

class Ludo {
public:
  Ludo();
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

  MapConfig config;
  std::shared_ptr<Map> map;
  std::vector<Player> players;
  bool humanMove;
  QRandomGenerator rng;

  GameState state;
};
} // namespace QtLudo
