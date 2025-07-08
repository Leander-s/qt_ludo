#include "GameWidget.h"

namespace QtLudo {
GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
  QStackedLayout *layout = new QStackedLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);

  openglwidget = new GameOpenGLWidget;
  pausemenu = new PauseMenuWidget;
  openglwidget->show();
  pausemenu->hide();
  paused = false;
  pausemenu->setContentsMargins(0, 0, 0, 0);

  layout->addWidget(openglwidget);
  layout->addWidget(pausemenu);
  pausemenu->raise();

  /*
  QTimer *timer = new QTimer;
  connect(timer, &QTimer::timeout, openglwidget,
  QOverload<>::of(&GameOpenGLWidget::update)); timer->start(16);
  */
  connect(openglwidget, &QOpenGLWidget::frameSwapped, openglwidget,
          QOverload<>::of(&GameOpenGLWidget::update));
  /*
  connect(openglwidget, &GameOpenGLWidget::pauseGame, this,
          &GameWidget::togglePause);
          */
  connect(pausemenu, &PauseMenuWidget::resumeGameSignal, pausemenu,
          &QWidget::hide);
  connect(pausemenu, &PauseMenuWidget::quitGameSignal, this,
          &GameWidget::quitToMenu);
}

void GameWidget::togglePause() {
  if (paused) {
    pausemenu->hide();
    paused = false;
  } else {
    pausemenu->show();
    paused = true;
  }
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    togglePause();
  }

  if (event->key() == Qt::Key_1){
  }

  if (event->key() == Qt::Key_1){
  }

  if (event->key() == Qt::Key_1){
  }

  if (event->key() == Qt::Key_1){
  }
}
} // namespace QtLudo
