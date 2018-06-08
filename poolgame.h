#ifndef POOLGAME_H
#define POOLGAME_H

#include <vector>
#include <QPainter>
#include <QSize>

#include "table.h"
#include "ball.h"

#include "changeinpoolgame.h"

/* IDEA:
 * Poolgame as originator(for Momento)
 * Creates a structure that stores a vector containing a copy
 * of the balls in the m_balls vector, and a pointer pointing to
 * a copy of the table.
 * TODO:
 * Momento functions in poolgame
 * Momento class
 * Caretaker class
 * REQUIREMENTS:
 * Copy constructor on Ball and Table class DONE
 *
 * NEW IDEA:
 * instead of signals, implement a mediator between the poolgame and caretaker classes
 */

/**
 * @brief The PoolGame class runs the pool game, it is in charge of the physics of the pool game as well as
 * drawing the game
 */
class PoolGame
{
public:
    /**
     * @brief PoolGame constructor
     * @param m_table a pointer to a Table object, Poolgame takes ownership of this pointer
     * @param balls a vector of pointers to balls, Poolgame takes ownership of all the contained pointers
     */
    PoolGame(Table * table,std::vector<Ball*> balls)
        : m_table(table),m_balls(balls)
    {}

    virtual ~PoolGame() {
        for(Ball * b: m_balls)
        {
            delete b;
        }
        delete m_table;
    }

    /**
     * @brief simulate one timestep of the game
     * @param timeStep is the period of time that this timestep is simulating
     */
    virtual void simulateTimeStep(float timeStep);

    /**
     * @brief draws all elements of the game, table and balls in that order
     * @param p is the painter which is used to paint the object
     */
    void draw(QPainter &p);

    /**
     * @brief size
     * @return the size of the game
     */
    QSize size(){return QSize(m_table->width(),m_table->height());}

    /**
     * @brief getBalls
     * @return the ball vector
     */
    std::vector<Ball*> getBalls() {return m_balls;}

    int stage() {return m_stage;}

protected:
    /**
     * @brief collide two balls if they are in contact
     * @param b1
     * @param b2
     * @return the change in the pool game after the collision
     */
    ChangeInPoolGame collide(Ball *b1, Ball *b2);


    Table * m_table;
    std::vector<Ball*> m_balls;
    int m_stage = 1;
};

#endif // POOLGAME_H
