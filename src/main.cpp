#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include "Menu.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QtLudo::Menu window;
  window.show();

  return app.exec();
}
