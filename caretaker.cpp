#include "caretaker.h"
#include <iostream>

Caretaker::Caretaker(QWidget* parent) {
    setParent(parent);
    m_rolledBack = nullptr;
}

void Caretaker::addMemento(PoolGameMomento *m) {

    m_momentos.push_back(m);
    m_rolledBack = nullptr;
}

PoolGameMomento* Caretaker::popMemento() {
    PoolGameMomento* memento = m_momentos.back();
    if (m_momentos.size() > 1) {
        m_momentos.pop_back();
    }
    m_rolledBack = memento;
    if (m_momentos.size() == 0) {
        m_momentos.push_back(memento);
    }
    return memento;
}

bool Caretaker::checkForMemento(Ball *b) {
    if(m_momentos.size() == 0) {
        return true;
    }
    QVector2D currPos = m_momentos.back()->getCueBallPosition();
    if (m_rolledBack != nullptr) {
        if(b->position() == m_rolledBack->getCueBallPosition()) {
            return false;
        }
    }
    if (b->position() == currPos) {
        return false;
    } else {
        return true;
    }
}

bool Caretaker::canRollback() {
    if (m_momentos.size() == 0) {
        return false;
    }
    return true;
}
