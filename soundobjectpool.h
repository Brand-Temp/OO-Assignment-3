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
    void setMaxPoolSize(int size);
private:
    SoundObjectPool();
protected:
    std::vector<QSound*> m_sounds;
    int max_size;
};

#endif // SOUNDOBJECTPOOL_H
