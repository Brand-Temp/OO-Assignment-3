#include "facade.h"

Facade::Facade()
{

}

void Facade::makeGame() {
    PoolGame* game = Initializer().createPoolgame("../OO-Assignment-3/config.json",&m_window);
    Caretaker* caretaker = new Caretaker(&m_window);
    game->setCaretaker(caretaker);

    m_game = game;
    m_caretaker = caretaker;
}

void Facade::showGame() {
    if(!m_game) return;
    m_window.show();
    m_window.start(m_game);
}
