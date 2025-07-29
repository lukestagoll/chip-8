#pragma once
#include <QAudioOutput>

class AudioOutput
{
  public:
    AudioOutput() { audioOutput_ = new QAudioOutput(); }
    ~AudioOutput() { delete audioOutput_; }
    QAudioOutput *get() const { return audioOutput_; }

  private:
    QAudioOutput *audioOutput_ = nullptr;
};
