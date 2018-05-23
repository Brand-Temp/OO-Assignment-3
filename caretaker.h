#ifndef CARETAKER_H
#define CARETAKER_H
#include "momento.h"
#include "dialog.h"

class Caretaker {
private:
    std::vector<PoolGameMomento*> m_momentos;
public:
    Caretaker() {}
public slots:
    void rPressed(QKeyEvent* event);
};s

#endif // CARETAKER_H
