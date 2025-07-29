#pragma once

#include <QMainWindow>
#include <QWidget>

#include "AudioOutput.h"
#include "Chip8.h"
#include "Chip8Display.h"
#include "EmulationClock.h"
#include "SoundEffect.h"
#include "Widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(const char *romFile, QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void runCycle();

  private:
    Widget *widget_ = nullptr;

    AudioOutput audioOutput_;
    SoundEffect beep_;

    Chip8 chip8_;
    Chip8Display *display_ = nullptr;
    EmulationClock emuClock_;
};
