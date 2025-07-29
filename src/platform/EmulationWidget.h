#pragma once

#include <QChronoTimer>
#include <QImage>
#include <QKeyEvent>
#include <QWidget>

#include "AudioOutput.h"
#include "Chip8.h"
#include "Chip8Display.h"
#include "EmulationClock.h"
#include "Keymap.h"
#include "SoundEffect.h"

class EmulationWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit EmulationWidget(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void setFramebuffer(const uint8_t *fb);
    void updateFrameBuffer(const uint8_t *framebuffer);

  public slots:
    int loadROM();
    void startEmulation();
    void stopEmulation();
    void pauseEmulation();

  protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

  private slots:
    void runCycle();

  private:
    QSize imageSize{Chip8Display::WIDTH, Chip8Display::HEIGHT};
    QImage image{imageSize, QImage::Format_Grayscale8};
    Keymap keymap_;

    AudioOutput audioOutput_;
    SoundEffect beep_;

    Chip8 chip8_;
    Chip8Display *display_ = nullptr;
    EmulationClock emuClock_;

    QChronoTimer *chronoTimer = nullptr;
};
