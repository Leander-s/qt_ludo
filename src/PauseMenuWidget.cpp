#include "PauseMenuWidget.h"

namespace QtLudo {
PauseMenuWidget::PauseMenuWidget(QWidget *parent) : QWidget(parent) {
  setStyleSheet("background-color:rgba(0,0,0,160);");
  setAttribute(Qt::WA_TransparentForMouseEvents, false);
  setFocusPolicy(Qt::StrongFocus);

  connect(resumeButton, &QPushButton::clicked, this,
          &PauseMenuWidget::resumeGame);
  connect(quitButton, &QPushButton::clicked, this, &PauseMenuWidget::quitGame);
}

void PauseMenuWidget::resumeGame() { emit resumeGameSignal(); }

void PauseMenuWidget::quitGame() { emit quitGameSignal(); }
} // namespace QtLudo
