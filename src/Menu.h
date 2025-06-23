#pragma once

#include <QLabel>
#include <QMainWindow>
#include <QWidget>
#include <ui_Menu.h>

class QPushButton;

namespace QtLudo {
class Menu : public QWidget {
  Q_OBJECT

public:
  Menu(QWidget *parent = nullptr);

private slots:
  void onButtonClicked();

private:
  Ui::Menu ui;
  int counter;
};
} // namespace QtLudo
