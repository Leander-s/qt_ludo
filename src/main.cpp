// Mine
#include <MainWindow.h>

// Qt
#include <QApplication>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QtLudo::LudoWindow *window = new QtLudo::LudoWindow;
  window->show();

  return app.exec();
}
