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
    void onStartButtonClicked();

signals:
    void startGame();

private:
  Ui::Menu ui;
};
} // namespace QtLudo
