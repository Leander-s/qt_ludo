#include "PauseMenuWidget.h"

namespace QtLudo {
PauseMenuWidget::PauseMenuWidget(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);
  setAttribute(Qt::WA_TransparentForMouseEvents, false);
  setFocusPolicy(Qt::StrongFocus);

  ui.resumeButton->setText("Resume");
  ui.quitButton->setText("Quit to menu");

  connect(ui.resumeButton, &QPushButton::clicked, this,
          &PauseMenuWidget::resumeGame);
  connect(ui.quitButton, &QPushButton::clicked, this, &PauseMenuWidget::quitGame);
}

void PauseMenuWidget::resumeGame() { emit resumeGameSignal(); }

void PauseMenuWidget::quitGame() { 
    this->hide();
    emit quitGameSignal(); 
}
} // namespace QtLudo
