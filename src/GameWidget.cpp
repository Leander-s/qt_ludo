#include "GameWidget.h"

namespace QtLudo {
GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
  QStackedLayout *layout = new QStackedLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);

  openglwidget = new GameOpenGLWidget;
  pausemenu = new PauseMenuWidget;
  openglwidget->show();
  pausemenu->hide();
  pausemenu->setContentsMargins(0, 0, 0, 0);

  layout->addWidget(openglwidget);
  layout->addWidget(pausemenu);
  pausemenu->raise();

  QTimer *timer = new QTimer;
  connect(timer, &QTimer::timeout, openglwidget, QOverload<>::of(&GameOpenGLWidget::update));
  connect(openglwidget, &GameOpenGLWidget::pauseGame, pausemenu,
          &QWidget::show);
  connect(pausemenu, &PauseMenuWidget::resumeGameSignal, pausemenu,
          &QWidget::hide);
  connect(pausemenu, &PauseMenuWidget::quitGameSignal, this,
          &GameWidget::quitToMenu);
  timer->start(8);
}
} // namespace QtLudo
