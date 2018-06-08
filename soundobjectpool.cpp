#include "soundobjectpool.h"

SoundObjectPool::SoundObjectPool()
{
    max_size = 5;
    curr_size = 0;
    ball = new QSoundEffect();
    ball->setSource(QUrl("qrc:/resources/sounds/ballCollision.wav"));
    ball->setVolume(1.0f);
    ball->setLoopCount(1);
    table = new QSoundEffect();
    table->setSource(QUrl("qrc:/resources/sounds/tableCollision.wav"));
    table->setVolume(1.0f);
    table->setLoopCount(0);
    bbreak = new QSoundEffect();
    bbreak->setSource(QUrl("qrc:/resources/sounds/ballBreak.wav"));
    bbreak->setVolume(1.0f);
    bbreak->setLoopCount(1);
}

void SoundObjectPool::setMaxPoolSize(int size) {
    max_size = size;
}

QSoundEffect* SoundObjectPool::acquireSound(std::string s) {
    if(s == "ball") {
        return ball;
    } else if (s == "table") {
        return table;
    } else if (s=="break") {
        return bbreak;
    } else {
        return nullptr;
    }
}

void SoundObjectPool::releaseSound(QSoundEffect *in) {

}

SoundObjectPool* SoundObjectPool::getInstance() {
    return new SoundObjectPool();
}
