#include "Menu.h"
#include <QPushButton>
#include <QVBoxLayout>

namespace QtLudo{
Menu::Menu(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);

    ui.button->setText("Click me");
    ui.label->setText("Clickcounter: 0");
    connect(ui.button, &QPushButton::clicked, this, &Menu::onButtonClicked);
    counter = 0;
}

void Menu::onButtonClicked() {
    counter++;
    ui.label->setText(QString("Clickcounter: %1").arg(counter));
}
}
