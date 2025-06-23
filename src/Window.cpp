#include "Window.h"
#include <QPushButton>
#include <QVBoxLayout>

LudoWindow::LudoWindow(QWidget *parent) : QWidget(parent) {
    button = new QPushButton("Click Me", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(button);
    setLayout(layout);

    connect(button, &QPushButton::clicked, this, &LudoWindow::onButtonClicked);
    counter = 0;
}

void LudoWindow::onButtonClicked() {
    counter++;
}
