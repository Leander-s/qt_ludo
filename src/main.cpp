#include <QApplication>
#include <QLabel>
#include <QPushButton>

void onPressed(int &counter) { counter++; }

int main(int argc, char *argv[]) {
  int i = 0;
  QApplication app(argc, argv);
  QPushButton button("Hello Qt !");
  button.resize(200, 60);
  button.show();
  return app.exec();
}
