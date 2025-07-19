#pragma once
#include <QWidget>
#include <ui_HUD.h>

namespace QtLudo {
class HUDWidget : public QWidget {
  Q_OBJECT

public:
  HUDWidget(QWidget *parent = nullptr);
  void update(const quint8 die);

private:
  Ui::HUD ui;
  quint8 dieRoll;
};
} // namespace QtLudo
