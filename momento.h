#ifndef MOMENTO_H
#define MOMENTO_H
#include "ball.h"
#include "table.h"

class PoolGameMomento {
protected:
    std::vector<Ball*> m_balls; //! A vector of Ball pointers, in this case a previous configuration of the pooltable class's balls
    Table* m_table; //! A table pointer, in this case a previous configuration of the pooltable class's table
    QVector2D m_cueBallPosition;
public:
    PoolGameMomento() {}
    ~PoolGameMomento() {}

    /**
     * @brief getBalls
     * @return the mementos balls
     */
    std::vector<Ball*> getBalls() {return m_balls;}

    /**
     * @brief getTable
     * @return the mementos table
     */
    Table* getTable() {return m_table;}

    QVector2D getCueBallPosition() {return m_cueBallPosition;}

    void setCueBallPosition(Ball* b) {
        m_cueBallPosition = b->position();
    }

    void addBall(Ball* b) {m_balls.push_back(b);}
    void addTable(Table* t) {m_table = t;}
};

#endif // MOMENTO_H
