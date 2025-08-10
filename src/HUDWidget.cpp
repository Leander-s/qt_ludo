#include "HUDWidget.h"

namespace QtLudo {
HUDWidget::HUDWidget(QWidget *parent) : QWidget(parent) { ui.setupUi(this); }

void HUDWidget::update(const quint8 dieRoll) {
  ui.DieIndicator->setText("Rolled " + QString::number(dieRoll));
}
} // namespace QtLudo
