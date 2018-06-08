#ifndef SOUNDOBJECTPOOL_H
#define SOUNDOBJECTPOOL_H

#include <QObject>
#include <QSoundEffect>

class SoundObjectPool
{
public:
    static SoundObjectPool* getInstance();
    QSoundEffect* acquireSound(std::string s);
    void releaseSound(QSoundEffect* in);
    void setMaxPoolSize(int size);
private:
    SoundObjectPool();
protected:
    QSoundEffect* ball;
    QSoundEffect* table;
    QSoundEffect* bbreak;
    int max_size;
    int curr_size;
};

#endif // SOUNDOBJECTPOOL_H
