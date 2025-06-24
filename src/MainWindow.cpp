#include "MainWindow.h"

namespace QtLudo {
LudoWindow::LudoWindow(QWidget *parent) : QMainWindow(parent) {
  widgetStack = new QStackedWidget();
  setCentralWidget(widgetStack);

  menu = new Menu;

  widgetStack->addWidget(menu);

  widgetStack->setCurrentWidget(menu);

  connect(menu, &Menu::startGame, this, &LudoWindow::startGame);
};

void LudoWindow::startGame() {
  // widgetStack->setCurrentWidget(game);
}
} // namespace QtLudo
