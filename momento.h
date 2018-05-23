#ifndef MOMENTO_H
#define MOMENTO_H
#include "ball.h"
#include "table.h"
#include "poolgame.h"

class PoolGameMomento {
protected:
    std::vector<Ball*> m_balls; //! A vector of Ball pointers, in this case a previous configuration of the pooltable class's balls
    Table* m_table; //! A table pointer, in this case a previous configuration of the pooltable class's table
    friend class PoolGame;
public:
    PoolGameMomento() {}
    ~PoolGameMomento() {}

    /**
     * @brief copyBalls - copies the balls in vector balls into the vector m_balls
     * @param balls - a vector of Ball*, the vector of balls in the poolgame class
     */

    void copyBalls(std::vector<Ball*> balls);

    /**
     * @brief copyTable - copies the given table into m_table
     * @param table - a Table, the table from the poolgame class
     */

    void copyTable(Table* table);

    std::vector<Ball*> getBalls() {return m_balls;}
    Table* getTable() {return m_table;}
};

#endif // MOMENTO_H
