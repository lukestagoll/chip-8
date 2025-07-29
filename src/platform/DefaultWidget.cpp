#include "DefaultWidget.h"

#include <QPushButton>
#include <QVBoxLayout>

DefaultWidget::DefaultWidget(EmulationWidget *emulationWidget, QWidget *parent) : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    auto *button = new QPushButton("Load ROM", this);
    button->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen));
    button->setIconSize(QSize(32, 32));
    layout->addStretch();
    layout->addWidget(button, 0, Qt::AlignCenter);
    layout->addStretch();

    connect(button, &QPushButton::clicked, this, &DefaultWidget::loadROM);
}
