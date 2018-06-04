#ifndef CARETAKER_H
#define CARETAKER_H
#include "momento.h"

#include <QWidget>

class Caretaker : public QObject{
private:
    std::vector<PoolGameMomento*> m_momentos; //! a vector of mementos
public:
    /**
     * @brief Caretaker - constructor
     * @param parent - parent dialog to connect to keypress signal
     * @param game - the game this caretaker looks after
     */
    Caretaker(QWidget* parent = 0);

    /**
     * @brief checkForMemento - checks if the cueball is in the same position in the most recently added memento
     * @param m - a memento
     * @return true if there is already a memento at the current position, false otherwise
     */
    bool checkForMemento(Ball* b);

    void addMemento(PoolGameMomento* m);

    PoolGameMomento* popMemento();

    bool canRollback();
};

#endif // CARETAKER_H
