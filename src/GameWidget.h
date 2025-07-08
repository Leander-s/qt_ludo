#pragma once
#include "GameOpenGLWidget.h"
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

private:
  GameOpenGLWidget *openglwidget;
  PauseMenuWidget *pausemenu;
  bool paused;

  void keyPressEvent(QKeyEvent *event) override;

signals:
  void quitToMenu();

private slots:
  void togglePause();
};
} // namespace QtLudo
