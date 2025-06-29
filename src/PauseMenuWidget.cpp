#include "PauseMenuWidget.h"

namespace QtLudo {
PauseMenuWidget::PauseMenuWidget(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);
  setAttribute(Qt::WA_TransparentForMouseEvents, false);
  setFocusPolicy(Qt::StrongFocus);

  ui.resumeButton->setText("Resume");
  ui.quitButton->setText("Quit to menu");
  ui.resumeButton->setMinimumWidth(600);
  ui.resumeButton->setMinimumHeight(50);
  ui.quitButton->setMinimumWidth(600);
  ui.quitButton->setMinimumHeight(50);
  ui.title->setMinimumWidth(600);
  ui.title->setMinimumHeight(100);

  connect(ui.resumeButton, &QPushButton::clicked, this,
          &PauseMenuWidget::resumeGame);
  connect(ui.quitButton, &QPushButton::clicked, this,
          &PauseMenuWidget::quitGame);
}

void PauseMenuWidget::resumeGame() { emit resumeGameSignal(); }

void PauseMenuWidget::quitGame() {
  this->hide();
  emit quitGameSignal();
}
} // namespace QtLudo
