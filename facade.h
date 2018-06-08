#ifndef FACADE_H
#define FACADE_H

#include "dialog.h"
#include "stage3dialog.h"
#include "initializer.h"
#include "poolgame.h"
#include "stage3game.h"
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
    Stage3Dialog m_3window;
};

#endif // FACADE_H
