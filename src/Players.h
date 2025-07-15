#pragma once
#include "Map.h"
#include "State.h"

namespace QtLudo {
class Controller : public QObject {
  Q_OBJECT
public slots:
};

enum Strategy { human, oneManArmy, youNeverWalkAlone, pacifist, killer };

struct aiParameters {
  const quint8 preferredFigurePosition;
  const int figurePositionBias;
  const int aggressionBias;
  const int defenseBias;
  const int willToLive;
};

const aiParameters oneManArmyPreset{
    .preferredFigurePosition = 0,
    .figurePositionBias = 100,
    .aggressionBias = 50,
    .defenseBias = 0,
    .willToLive = 100,
};

const aiParameters youNeverWalkAlonePreset{
    .preferredFigurePosition = 255,
    .figurePositionBias = 100,
    .aggressionBias = 50,
    .defenseBias = 100,
    .willToLive = 100,
};

const aiParameters pacifistPreset{
    .preferredFigurePosition = 0,
    .figurePositionBias = 10,
    .aggressionBias = -100,
    .defenseBias = 100,
    .willToLive = 100,
};

const aiParameters killerPreset{
    .preferredFigurePosition = 255,
    .figurePositionBias = 10,
    .aggressionBias = 100,
    .defenseBias = 0,
    .willToLive = 100,
};

class Player {
public:
  Player(const LudoColor _color);
  const QVector<bool> getPossibleMoves(const quint8 *positions,
                                       const quint8 playerOffset,
                                       const quint8 roll,
                                       const MapConfig &config) const;
  void sortPositions(const quint8 *playerPositions, quint8 *sortedPositions,
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
  AIPlayer(const LudoColor _color, const aiParameters &_params);
  const quint8 decide(const quint8 *positions, const quint8 roll,
                      const MapConfig &config, const quint8 playerOffset) const;
  const int calculateScore(const quint8 *positions, const quint8 playerPosition,
                           const quint8 sortedPosition, const quint8 roll,
                           const MapConfig &config,
                           const quint8 playerOffset) const;

  const aiParameters params;
};
} // namespace QtLudo
