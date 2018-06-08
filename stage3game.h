#ifndef STAGE3GAME_H
#define STAGE3GAME_H

#include "poolgame.h"
#include "momento.h"
#include "caretaker.h"

#include "soundobjectpool.h"
#include "randomballgenerator.h"


class Stage3Game : public PoolGame
{
public:
    Stage3Game(Table * table,std::vector<Ball*> balls)
        : PoolGame(table, balls)
    {}

    ~Stage3Game() {
        for(Ball * b: m_balls)
        {
            delete b;
        }
        delete m_table;
    }

    /* IDEA:
     * turn Momento into a template class which can work with other objects
     */

    /* IDEA:
     * use an observer to interface between Game and Caretaker
     */

    /**
     * @brief createMomento - creates a new momento of the current game state
     * @return a new Momento object containing a copy of the current game state
     */
    PoolGameMomento* createMomento();

    /**
     * @brief setState - change the current state of the game
     * @param m - a Momento containing the state to return to
     */
    void setState(PoolGameMomento* m);

    /**
     * @brief setCaretaker - sets the caretaker
     * @param c - a caretaker
     */
    void setCaretaker(Caretaker* c);

    /**
     * @brief rollback - call on the caretaker to rollback the board
     */
    void rollback();

     /**
     * @brief setSoundPool - sets m_soundPool
     * @param pool - a SoundObjectPool*
     */
    void setSoundPool(SoundObjectPool* pool) {m_soundPool = pool;}

    /**
     * @brief randomBall - gets a random ball from the generator and adds it to m_balls
     */
    void randomBall();

    /**
     * @brief setStage sets the stage number
     * @param s sets stage (it will be 3)
     */
    void setStage(int s) {m_stage = s;}

    void simulateTimeStep(float timeStep);

    /**
     * @brief playBackground plays background music
     */
    void playBackground();
protected:
    Caretaker* m_caretaker;
    SoundObjectPool* m_soundPool;
};

#endif // STAGE3GAME_H
