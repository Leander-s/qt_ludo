#include "GameWidget.h"

namespace QtLudo{
    GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);

        openglwidget = new GameOpenGLWidget;
        pausemenu = new PauseMenuWidget;
        pausemenu->hide();

        layout->addWidget(openglwidget);
        layout->addWidget(pausemenu);

        connect(openglwidget, &GameOpenGLWidget::pauseGame, pausemenu, &QWidget::show);
        connect(pausemenu, &PauseMenuWidget::resumeGame, pausemenu, &QWidget::hide);
        connect(pausemenu, &PauseMenuWidget::quitGame, this, &GameWidget::quitToMenu);
    }
}
