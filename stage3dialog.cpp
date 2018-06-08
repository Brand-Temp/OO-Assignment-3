#include "stage3dialog.h"
#include "stage3game.h"

constexpr float fps = 60;
constexpr float timeStep = 0.01;

Stage3Dialog::Stage3Dialog(QWidget *parent)
    : Dialog(parent), m_secondTimer(new QTimer())
{

}

void Stage3Dialog::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_R) {
        dynamic_cast<Stage3Game*>(m_game)->rollback();
    }
}

void Stage3Dialog::secondTimer() {
    dynamic_cast<Stage3Game*>(m_game)->randomBall();
}

void Stage3Dialog::start(PoolGame *game)
{
    m_game = game;
    this->setMinimumSize(m_game->size());
    this->resize(m_game->size());
    connect(m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(m_timestepTimer,SIGNAL(timeout()),this,SLOT(runSimulationStep()));
    connect(m_secondTimer,SIGNAL(timeout()),this,SLOT(secondTimer()));
    m_framerateTimer->start(1000/fps);
    m_timestepTimer->start(1000*timeStep);
    m_secondTimer->start(5000);
    dynamic_cast<Stage3Game*>(game)->playBackground();
}

Stage3Dialog::~Stage3Dialog()
{
    delete m_game;
    delete m_framerateTimer;
    delete m_timestepTimer;
    delete m_secondTimer;
}
