#pragma once
#include <QPushButton>
#include <QWidget>
#include <ui_PauseMenuWidget.h>

namespace QtLudo {
class PauseMenuWidget : public QWidget {
  Q_OBJECT

public:
  PauseMenuWidget(QWidget *parent = nullptr);

signals:
  void resumeGameSignal();
  void quitGameSignal();

public slots:
  void resumeGame();
  void quitGame();

private:
  Ui::PauseMenu ui;
};
} // namespace QtLudo
