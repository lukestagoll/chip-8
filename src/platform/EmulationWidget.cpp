#include "EmulationWidget.h"
#include <QFileDialog>
#include <QPainter>

EmulationWidget::EmulationWidget(QWidget *parent)
    : QWidget(parent), audioOutput_(), beep_(audioOutput_.get(), QUrl("assets/audio/beep.wav"))
{
    setFocusPolicy(Qt::StrongFocus);

    chronoTimer = new QChronoTimer(this);
    connect(chronoTimer, &QChronoTimer::timeout, this, &EmulationWidget::runCycle);
}

QSize EmulationWidget::minimumSizeHint() const
{
    return QSize(320, 160);
}

QSize EmulationWidget::sizeHint() const
{
    return QSize(640, 320);
}

void EmulationWidget::runCycle()
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
            updateFrameBuffer(chip8_.getDisplayBuffer());
            chip8_.clearDrawFlag();
        }
        ticksPerCycle++;
        emuClock_.consumeTick();
    }

    chip8_.updateTimers();
}

void EmulationWidget::updateFrameBuffer(const uint8_t *framebuffer)
{
    for (int y = 0; y < imageSize.height(); y++)
    {
        uint8_t *line = image.scanLine(y);
        const uint8_t *srcLine = framebuffer + y * imageSize.width();

        for (int x = 0; x < imageSize.width(); x++)
        {
            line[x] = srcLine[x] * 255;
        }
    }

    update();
}

void EmulationWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(rect(), image);
}

void EmulationWidget::keyPressEvent(QKeyEvent *event)
{
    Action key = keymap_.getKey(event->key());
    if (key != Action::NONE)
    {
        chip8_.keydown(key);
    }
}

void EmulationWidget::keyReleaseEvent(QKeyEvent *event)
{
    Action key = keymap_.getKey(event->key());
    if (key != Action::NONE)
    {
        chip8_.keyup(key);
    }
}

int EmulationWidget::loadROM()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load Rom", "", ".ch8");
    int result = chip8_.loadROM(fileName.toUtf8().constData());
    if (result != 0)
    {
        chip8_.init();
        return chip8_.restart();
    }
    return result;
}

void EmulationWidget::startEmulation()
{
    if (chip8_.playingAudio())
    {
        beep_.start();
    }
    chronoTimer->start();
    if (!chip8_.isPaused())
    {
        chip8_.restart();
    }
}

void EmulationWidget::stopEmulation()
{
    chronoTimer->stop();
    if (chip8_.playingAudio())
    {
        beep_.stop();
    }
    chip8_.init();
}

void EmulationWidget::pauseEmulation()
{
    if (chip8_.isPaused())
    {
        return;
    }
    chronoTimer->stop();
    if (chip8_.playingAudio())
    {
        beep_.stop();
    }

    chip8_.pause();
}