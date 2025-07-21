#pragma once
#include "Game.h"
#include "GameOpenGLWidget.h"
#include "HUDWidget.h"
#include "Map.h"
#include "PauseMenuWidget.h"
#include <QSizePolicy>
#include <QStackedLayout>
#include <QTimer>
#include <QWidget>
#include <memory>

namespace QtLudo {
struct currentPlayer {
    quint8 index;
    quint8 offset;
    Player *player;
    QVector<bool> possibleMoves;
    quint8 roll;
    quint8 choice;
};

class GameWidget : public QWidget {
  Q_OBJECT

public:
  GameWidget(QWidget *parent = nullptr);
  void startGame();

private:
  GameOpenGLWidget *openglwidget;
  std::shared_ptr<PauseMenuWidget> pausemenu;
  std::unique_ptr<HUDWidget> hud;
  Ludo *game;
  Map map;
  bool paused;
  currentPlayer player;

  void keyPressEvent(QKeyEvent *event) override;
  void getNewGameState();
  void setNewGameState();

signals:
  void quitToMenu();

private slots:
  // void humanCommitted();
  void togglePause();
};
} // namespace QtLudo
