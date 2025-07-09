#pragma once
#include <QObject>
#include "State.h"

namespace QtLudo {
class Controller : public QObject {
  Q_OBJECT
public slots:
  void startTurn();
  void applyMove();
};

enum AiStrategy {oneManArmy};
class Player {
  bool moving;

public:
  LudoColor color;
  int decide();
};

class Human : Player {
  int decide();

private:
  Controller controller;
};

class AI : Player {
public:
  AiStrategy strategy;
  int decide(int positions[16]);
};
} // namespace QtLudo
