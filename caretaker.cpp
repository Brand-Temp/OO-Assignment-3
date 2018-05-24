#include "caretaker.h"
#include "stage2ball.h"

Caretaker::checkForMomento() {
    std::vector<Ball*> balls = m_game->getBalls();
    for (Stage2Ball* b : balls) {
        if (b->getCue()) {
            m_momentos.push_back(m_game->createMomento());
        }
    }
}

Caretaker::rPressed(QKeyEvent *event) {
    m_game->setState(m_momentos.pop_back());
}
