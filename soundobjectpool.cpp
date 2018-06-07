#include "soundobjectpool.h"

SoundObjectPool::SoundObjectPool()
{

}

QSound* SoundObjectPool::acquireSound(int i) {
    QSound* temp;
    return temp;
}

void SoundObjectPool::releaseSound(QSound *in) {
    m_sounds[i] = in;
}

SoundObjectPool* SoundObjectPool::getInstance() {
    return new SoundObjectPool();
}
