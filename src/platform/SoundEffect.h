#pragma once
#include <QAudioOutput>
#include <QMediaPlayer>

class SoundEffect
{
  public:
    SoundEffect(QAudioOutput *output, QUrl url);
    void start();
    void stop();
    QMediaPlayer *get() { return soundEffect_; }

  private:
    QMediaPlayer *soundEffect_ = nullptr;
};
