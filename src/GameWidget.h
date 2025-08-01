#pragma once
#include "GameOpenGLWidget.h"
#include "Game.h"
#include "PauseMenuWidget.h"
#include <QWidget>
#include <QStackedLayout>
#include <QSizePolicy>
#include <QTimer>

namespace QtLudo {
class GameWidget : public QWidget {
  Q_OBJECT

public:
  GameWidget(QWidget *parent = nullptr);
  void startGame();

private:
  GameOpenGLWidget *openglwidget;
  PauseMenuWidget *pausemenu;
  bool paused;
  Ludo *game;
  MapConfig config;
  uint8_t lastDieRoll;

  void keyPressEvent(QKeyEvent *event) override;
  void updateGameState();

signals:
  void quitToMenu();

private slots:
  void togglePause();
};
} // namespace QtLudo
