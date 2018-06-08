#include "facade.h"
#include <time.h>

Facade::Facade()
{

}

void Facade::makeGame() {
    // adjust this to seed as needed
    srand(float(clock()));
    PoolGame* game = Initializer().createPoolgame("../OO-Assignment-3/config.json",&m_window,&m_3window);
    Caretaker* caretaker = new Caretaker(&m_window);

    if(game->stage() == 3) {
        caretaker = new Caretaker(&m_3window);
        dynamic_cast<Stage3Game*>(game)->setCaretaker(caretaker);
        dynamic_cast<Stage3Game*>(game)->setSoundPool(SoundObjectPool::getInstance());
    }
    m_game = game;
    m_caretaker = caretaker;
}

void Facade::showGame() {
    if(!m_game) return;
    if (m_game->stage() == 3) {
        m_3window.show();
        m_3window.start(m_game);
        return;
    }
    m_window.show();
    m_window.start(m_game);
}
