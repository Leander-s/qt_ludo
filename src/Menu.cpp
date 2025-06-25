#include "Menu.h"
#include <QPushButton>
#include <QVBoxLayout>

namespace QtLudo{
Menu::Menu(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    ui.startButton->setText("Start game");
    ui.quitButton->setText("Quit");
    ui.startButton->setMinimumWidth(600);
    ui.startButton->setMinimumHeight(50);
    ui.quitButton->setMinimumWidth(600);
    ui.quitButton->setMinimumHeight(50);

    ui.title->setMinimumWidth(600);
    ui.title->setMinimumHeight(100);

    connect(ui.startButton, &QPushButton::clicked, this, &Menu::onStartButtonClicked);
    connect(ui.quitButton, &QPushButton::clicked, this, &QApplication::quit);
}

void Menu::onStartButtonClicked() {
    emit startGame();
}

}
