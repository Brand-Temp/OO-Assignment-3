#include "caretaker.h"
#include <iostream>

Caretaker::Caretaker(QWidget* parent) {
    setParent(parent);
}

void Caretaker::addMemento(PoolGameMomento *m) {
    m_momentos.push_back(m);
}

PoolGameMomento* Caretaker::popMemento() {
    PoolGameMomento* memento = m_momentos.back();
    m_momentos.pop_back();
    return memento;
}

bool Caretaker::checkForMemento(Ball *b) {
    if(m_momentos.size() == 0) {
        return true;
    }
    QVector2D currPos = m_momentos.back()->getCueBallPosition();
    if (b->position() == currPos) {
        return false;
    } else {
        return true;
    }
}

bool Caretaker::canRollback() {
    if (m_momentos.size() < 1) {
        return false;
    }
    return true;
}
