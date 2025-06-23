#pragma once

#include <QWidget>

class QPushButton;

class LudoWindow : public QWidget {
  Q_OBJECT

public:
  LudoWindow(QWidget *parent = nullptr);

private slots:
  int counter;
  void onButtonClicked();

private:
  QPushButton *button;
};
