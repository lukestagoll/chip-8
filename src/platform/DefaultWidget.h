#pragma once
#include "EmulationWidget.h"

#include <QWidget>

class DefaultWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit DefaultWidget(EmulationWidget *emulationWidget, QWidget *parent = nullptr);

  signals:
    void loadROM();
};
