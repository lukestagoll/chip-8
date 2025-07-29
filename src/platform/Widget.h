#pragma once

#include <QImage>
#include <QKeyEvent>
#include <QWidget>

#include "Chip8.h"
#include "Chip8Display.h"
#include "Keymap.h"

class Widget : public QWidget
{
    Q_OBJECT

  public:
    explicit Widget(Chip8 *chip8 = nullptr, QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void setFramebuffer(const uint8_t *fb);
    void updateFrameBuffer(const uint8_t *framebuffer);

  protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

  private:
    QSize imageSize{Chip8Display::WIDTH, Chip8Display::HEIGHT};
    QImage image{imageSize, QImage::Format_Grayscale8};
    Keymap keymap_;
    Chip8 *chip8_;
};
