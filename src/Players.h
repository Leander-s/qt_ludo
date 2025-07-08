#pragma once
#include <QObject>

namespace QtLudo {
class Controller : public QObject {
  Q_OBJECT
public slots:
  void startTurn();
  void applyMove();
};

enum AiStrategy {oneManArmy};
enum LudoColor { red, blue, yellow, green };
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
