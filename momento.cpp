#include "momento.h"

PoolGameMomento::copyBalls(std::vector<Ball *> balls) {
    for (Ball* b : balls) {
        m_balls.push_back(new Ball(b));
    }
}

PoolGameMomento::copyTable(Table *table) {
    m_table = table;
}
