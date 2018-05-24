#ifndef CARETAKER_H
#define CARETAKER_H
#include "momento.h"
#include "dialog.h"
#include <QWidget>

class Caretaker : public QObject{
private:
    std::vector<PoolGameMomento*> m_momentos;
    PoolGame* m_game;
public:
    Caretaker() {}
    /**
     * @brief Caretaker - constructor
     * @param parent - parent dialog to connect to keypress signal
     * @param game - the game this caretaker looks after
     */
    Caretaker(PoolGame* game, Dialog* parent) : m_game(game) {
        connect(parent, &Dialog::rPressed, this, &Caretaker::rPressed);
        connect(game, &PoolGame::checkForMomento, this, &Caretaker::checkForMomento);
    }
public slots:
    void rPressed(QKeyEvent* event);
    void checkForMomento();
};

#endif // CARETAKER_H
