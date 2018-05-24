#ifndef POOLGAME_H
#define POOLGAME_H

#include <vector>
#include <QPainter>
#include <QSize>

#include "table.h"
#include "ball.h"

#include "changeinpoolgame.h"

#include "momento.h"

/* IDEA:
 * Poolgame as originator(for Momento)
 * Creates a structure that stores a vector containing a copy
 * of the balls in the m_balls vector, and a pointer pointing to
 * a copy of the table.
 * TODO:
 * Momento functions in poolgame
 * Momento class
 * The other class -- in this case PoolGame might be its own originator and caretaker, is that allowed?
 * REQUIREMENTS:
 * Copy constructor on Ball and Table class DONE
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
    PoolGame(Table * m_table,std::vector<Ball*> balls)
        :m_table(m_table),m_balls(balls)
    {}

    ~PoolGame();

    /**
     * @brief simulate one timestep of the game
     * @param timeStep is the period of time that this timestep is simulating
     */
    void simulateTimeStep(float timeStep);

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

    /* IDEA:
     * turn Momento into a template class which can work with other objects
     */

    /**
     * @brief createMomento - creates a new momento of the current game state
     * @return a new Momento object containing a copy of the current game state
     */
    PoolGameMomento createMomento();

    /**
     * @brief setState - change the current state of the game
     * @param m - a Momento containing the state to return to
     */
    void setState(PoolGameMomento m);

signals:
    /**
     * @brief chekForMomento - signal emitted when the positions and velocities of ball have been updated
     * Tells the caretaker to check for a momento creation
     */
    void checkForMomento();

private:
    /**
     * @brief collide two balls if they are in contact
     * @param b1
     * @param b2
     * @return the change in the pool game after the collision
     */
    ChangeInPoolGame collide(Ball *b1, Ball *b2);


    Table * m_table;
    std::vector<Ball*> m_balls;
};

#endif // POOLGAME_H
