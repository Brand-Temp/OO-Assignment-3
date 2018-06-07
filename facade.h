#ifndef FACADE_H
#define FACADE_H

#include "dialog.h"
#include "initializer.h"
#include "poolgame.h"
#include "caretaker.h"

class Facade
{
public:
    Facade();
    /**
     * @brief makeGame - creates the classes necessary for a game
     */
    void makeGame();
    /**
     * @brief showGame - displays the game
     */
    void showGame();
protected:
    PoolGame* m_game;
    Caretaker* m_caretaker;
    Dialog m_window;
};

#endif // FACADE_H
