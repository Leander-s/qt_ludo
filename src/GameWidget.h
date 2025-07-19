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
  quint8 lastDieRoll;

  void keyPressEvent(QKeyEvent *event) override;
  void updateGameState();

signals:
  void quitToMenu();

private slots:
  void togglePause();
};
} // namespace QtLudo
