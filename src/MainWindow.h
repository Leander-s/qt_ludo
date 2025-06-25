#include "GameWidget.h"
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
  GameWidget *gameWidget;

private slots:
  void startGame();
  void returnToMenu();
};
} // namespace QtLudo
