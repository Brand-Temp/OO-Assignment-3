#include "soundobjectpool.h"

SoundObjectPool::SoundObjectPool()
{
    max_size = 5;
}

void SoundObjectPool::setMaxPoolSize(int size) {
    max_size = size;
}

QSound* SoundObjectPool::acquireSound(int i) {
    if(m_sounds.size() == 0) {
        return new QSound();
    }
    QSound* temp = m_sounds.back();
    m_sounds.pop_back();
    return temp;
}

void SoundObjectPool::releaseSound(QSound *in) {
    if (m_sounds.size() + 1 < max_size) {
        m_sounds.push_back(in);
    } else {
        delete in;
    }
}

SoundObjectPool* SoundObjectPool::getInstance() {
    return new SoundObjectPool();
}
