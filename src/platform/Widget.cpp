#include "Widget.h"
#include <QPainter>

Widget::Widget(Chip8 *chip8, QWidget *parent) : QWidget(parent)
{
    chip8_ = chip8;
    setFocusPolicy(Qt::StrongFocus);
}

QSize Widget::minimumSizeHint() const
{
    return QSize(320, 160);
}

QSize Widget::sizeHint() const
{
    return QSize(640, 320);
}

void Widget::updateFrameBuffer(const uint8_t *framebuffer)
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

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(rect(), image);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    Action key = keymap_.getKey(event->key());
    if (key != Action::NONE)
    {
        chip8_->keydown(key);
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    Action key = keymap_.getKey(event->key());
    if (key != Action::NONE)
    {
        chip8_->keyup(key);
    }
}
