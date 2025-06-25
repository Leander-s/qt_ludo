#include "MainWindow.h"

namespace QtLudo {
LudoWindow::LudoWindow(QWidget *parent) : QMainWindow(parent) {
  widgetStack = new QStackedWidget();
  setCentralWidget(widgetStack);

  menu = new Menu;
  gameWidget = new GameWidget;

  widgetStack->addWidget(menu);
  widgetStack->addWidget(gameWidget);

  widgetStack->setCurrentWidget(menu);

  connect(menu, &Menu::startGame, this, &LudoWindow::startGame);
  connect(gameWidget, &GameWidget::quitToMenu, this, &LudoWindow::returnToMenu);
};

void LudoWindow::startGame() { widgetStack->setCurrentWidget(gameWidget); }

void LudoWindow::returnToMenu() { widgetStack->setCurrentWidget(menu); }
} // namespace QtLudo
