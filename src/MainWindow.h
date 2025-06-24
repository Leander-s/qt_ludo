#include "Menu.h"
#include <QMainWindow>
#include <QStackedWidget>

namespace QtLudo {
class LudoWindow : public QMainWindow {
  Q_OBJECT
public:
  LudoWindow(QWidget *parent = nullptr);

private:
  QStackedWidget *widgetStack;
  Menu *menu;

private slots:
  void startGame();
};
} // namespace QtLudo
