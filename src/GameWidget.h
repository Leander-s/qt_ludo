#pragma once
#include "Game.h"
#include "GameOpenGLWidget.h"
#include "Map.h"
#include "PauseMenuWidget.h"
#include <QSizePolicy>
#include <QStackedLayout>
#include <QTimer>
#include <QWidget>
#include <memory>

namespace QtLudo {
class GameWidget : public QWidget {
  Q_OBJECT

public:
  GameWidget(QWidget *parent = nullptr);
  void startGame();

private:
  std::shared_ptr<GameOpenGLWidget> openglwidget;
  std::shared_ptr<PauseMenuWidget> pausemenu;
  std::shared_ptr<Map> map;
  std::unique_ptr<Ludo> game;
  bool paused;
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
