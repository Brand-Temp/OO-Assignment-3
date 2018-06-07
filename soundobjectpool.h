#ifndef SOUNDOBJECTPOOL_H
#define SOUNDOBJECTPOOL_H

#include <QObject>
#include <QSound>

class SoundObjectPool
{
public:
    static SoundObjectPool* getInstance();
    QSound* acquireSound(int i);
    void releaseSound(QSound* in);
private:
    SoundObjectPool();
protected:
    QSound* m_sounds[];
};

#endif // SOUNDOBJECTPOOL_H
