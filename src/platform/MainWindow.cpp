#include "MainWindow.h"
#include "AudioOutput.h"
#include <QChronoTimer>

MainWindow::MainWindow(const char *romFile, QWidget *parent)
    : QMainWindow(parent), audioOutput_(), beep_(audioOutput_.get(), QUrl("assets/audio/beep.wav"))
{
    chip8_.loadROM(romFile);

    widget_ = new Widget(&chip8_, this);
    setCentralWidget(widget_);

    QChronoTimer *chronoTimer = new QChronoTimer(this);
    connect(chronoTimer, &QChronoTimer::timeout, this, &MainWindow::runCycle);
    chronoTimer->start();
}

MainWindow::~MainWindow()
{
    delete widget_;
}

void MainWindow::runCycle()
{
    emuClock_.update();

    if (chip8_.playingAudio()) beep_.start();
    else beep_.stop();
    int ticksPerCycle = 0;

    while (emuClock_.shouldTick())
    {
        CPUStatus status = chip8_.tick();
        if (status != CPUStatus::OK)
        {
            return exit(static_cast<int>(status));
        }

        if (chip8_.getDrawFlag())
        {
            widget_->updateFrameBuffer(chip8_.getDisplayBuffer());
            chip8_.clearDrawFlag();
        }
        ticksPerCycle++;
        emuClock_.consumeTick();
    }

    chip8_.updateTimers();
}
