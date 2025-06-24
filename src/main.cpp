#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QtLudo::LudoWindow *window = new QtLudo::LudoWindow;
  window->show();

  return app.exec();
}
