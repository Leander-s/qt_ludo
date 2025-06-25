#pragma once
#include <QPushButton>
#include <QWidget>

namespace QtLudo {
class PauseMenuWidget : public QWidget {
  Q_OBJECT

public:
  PauseMenuWidget(QWidget *parent = nullptr);

private:
  QPushButton resumeButton;
  QPushButton quitButton;

signals:
  void resumeGameSignal();
  void quitGameSignal();

private slots:
  void resumeGame();
  void quitGame();
};
} // namespace QtLudo
