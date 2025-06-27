#include "GameWidget.h"

namespace QtLudo {
GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
  QStackedLayout *layout = new QStackedLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);

  openglwidget = new GameOpenGLWidget;
  pausemenu = new PauseMenuWidget;
  pausemenu->hide();
  pausemenu->setContentsMargins(0, 0, 0, 0);

  layout->addWidget(openglwidget);
  layout->addWidget(pausemenu);
  pausemenu->raise();

  connect(openglwidget, &GameOpenGLWidget::pauseGame, pausemenu,
          &QWidget::show);
  connect(pausemenu, &PauseMenuWidget::resumeGameSignal, pausemenu,
          &QWidget::hide);
  connect(pausemenu, &PauseMenuWidget::quitGameSignal, this,
          &GameWidget::quitToMenu);
}
} // namespace QtLudo
