#include "stage3game.h"
#include "cueballdecorator.h"
#include <iostream>

PoolGameMomento* Stage3Game::createMomento() {
    PoolGameMomento* m = new PoolGameMomento();
    m->addTable(m_table);
    for (Ball* b: m_balls) {
        if(!(dynamic_cast<CueBallDecorator*>(b) == nullptr)) {
            m->setCueBallPosition(b);
        }
        m->addBall(b->copy());
    }
    return m;
}

void Stage3Game::setState(PoolGameMomento* m) {
    m_balls = m->getBalls();
    m_table = m->getTable();
}

void Stage3Game::setCaretaker(Caretaker *c) {
    m_caretaker = c;
}

void Stage3Game::rollback() {
    if (m_caretaker->canRollback()) {
        setState(m_caretaker->popMemento());
    } else {
        std::cout << "Cannot roll back" << std::endl;
    }
    for(Ball* b: m_balls) {
        b->setCopy(false);
    }
}

void Stage3Game::randomBall() {
    RandomBallGenerator r = RandomBallGenerator();
    m_balls.push_back(r.getBall(m_table->width(), m_table->height()));
}

void Stage3Game::simulateTimeStep(float timeStep)
{
    ChangeInPoolGame totalChange;
    //collisions of balls with the edge of the table
    for(Ball * b: m_balls)
    {
        totalChange = totalChange.merge(m_table->ballCollision(b));
    }
    if (!totalChange.empty()) {
        QSoundEffect* s = m_soundPool->acquireSound();
        s->setSource(QUrl::fromLocalFile(":/resources/sounds/tableCollision.wav"));
        s->setLoopCount(1);
        s->setVolume(1);
        s->play();
        m_soundPool->releaseSound(s);
    }
    //a collision between each possible pair of balls
    for(unsigned int i = 0; i < m_balls.size();++i)
    {
        for(unsigned int j = i+1;j < m_balls.size();++j)
        {
            if(m_balls[i]->collidesWith(m_balls[j]))
            {
                totalChange = totalChange.merge(collide(m_balls[i],m_balls[j]));
            }
        }
    }

    for(Ball * e:totalChange.m_ballsToRemove)
    {
        m_balls.erase(std::find(m_balls.begin(),m_balls.end(),e));
    }

    for(Ball * a:totalChange.m_ballsToAdd)
    {
        m_balls.push_back(a);
    }

    for(Ball * b: m_balls)
    {
        b->move(timeStep);

        //apply friction
        b->changeVelocity(-m_table->friction()*timeStep*b->velocity());

        //if moving less than 5 pixels per second just stop
        if(b->velocity().length()<5)
            b->setVelocity(QVector2D(0,0));

        // if cueball check if memento should be made and make
        if(!(dynamic_cast<CueBallDecorator*>(b) == nullptr)) {
            if (b->velocity() == QVector2D(0,0)) {
                if (m_caretaker->checkForMemento(b)) {
                    PoolGameMomento* newMemento = createMomento();
                    m_caretaker->addMemento(newMemento);
                }
            }
        }
    }
}

void Stage3Game::playBackground() {
    QSoundEffect* s = m_soundPool->acquireSound();
    s->setVolume(1);
    s->setLoopCount(QSoundEffect::Infinite);
    s->play();
    std::cout<<"Playing music" << std::endl;
}
