#include "SoundEffect.h"

SoundEffect::SoundEffect(QAudioOutput *output, QUrl url)
{
    soundEffect_ = new QMediaPlayer();
    soundEffect_->setAudioOutput(output);
    soundEffect_->setSource(url);
    soundEffect_->setLoops(QMediaPlayer::Infinite);
}

void SoundEffect::start()
{
    soundEffect_->play();
}

void SoundEffect::stop()
{
    soundEffect_->stop();
}
