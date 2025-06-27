#pragma once
#include "GameOpenGLWidget.h"
#include "PauseMenuWidget.h"
#include <QWidget>
#include <QStackedLayout>
#include <QSizePolicy>

namespace QtLudo {
class GameWidget : public QWidget {
  Q_OBJECT

public:
  GameWidget(QWidget *parent = nullptr);

private:
  GameOpenGLWidget *openglwidget;
  PauseMenuWidget *pausemenu;

signals:
  void quitToMenu();
};
} // namespace QtLudo
