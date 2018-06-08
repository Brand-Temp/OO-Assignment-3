#ifndef SOUNDOBJECTPOOL_H
#define SOUNDOBJECTPOOL_H

#include <QObject>
#include <QSoundEffect>

class SoundObjectPool
{
public:
    static SoundObjectPool* getInstance();
    QSoundEffect* acquireSound(int i);
    void releaseSound(QSoundEffect* in);
    void setMaxPoolSize(int size);
private:
    SoundObjectPool();
protected:
    std::vector<QSoundEffect*> m_sounds;
    int max_size;
};

#endif // SOUNDOBJECTPOOL_H
