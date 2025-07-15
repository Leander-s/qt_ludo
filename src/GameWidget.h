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
  GameOpenGLWidget *openglwidget;
  std::shared_ptr<PauseMenuWidget> pausemenu;
  Ludo *game;
  Map map;
  bool paused;
  MapConfig config;
  quint32 lastDieRoll;

  void keyPressEvent(QKeyEvent *event) override;
  void updateGameState();

signals:
  void quitToMenu();

private slots:
  void togglePause();
};
} // namespace QtLudo
