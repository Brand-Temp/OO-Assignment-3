#include "stage3game.h"
#include "stage2table.h"
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
        QSoundEffect* s = m_soundPool->acquireSound("break");
        if (s == nullptr) {
           m_soundPool->releaseSound(s);
        } else {
            s->play();
            m_soundPool->releaseSound(s);
        }
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

}

ChangeInPoolGame Stage3Game::collide(Ball *b1, Ball *b2)
{
    //using the code provided for the collision mechanics

     //calculate their mass ratio
     float mR = b2->mass() / b1->mass();

     //calculate the axis of collision
     QVector2D collisionVector = b2->position() - b1->position();
     collisionVector.normalize();

    //the proportion of each balls velocity along the axis of collision
     double vA = QVector2D::dotProduct(collisionVector, b1->velocity());
     double vB = QVector2D::dotProduct(collisionVector, b2->velocity());
     //the balls are moving away from each other so do nothing
     if (vA <= 0 && vB >= 0) {
      return ChangeInPoolGame();
     }

     //The velocity of each ball after a collision can be found by solving the quadratic equation
     //given by equating momentum and energy before and after the collision and finding the velocities
     //that satisfy this
     //-(mR+1)x^2 2*(mR*vB+vA)x -((mR-1)*vB^2+2*vA*vB)=0
     //first we find the discriminant
     double a = -(mR + 1);
     double b = 2 * (mR * vB + vA);
     double c = -((mR - 1) * vB * vB + 2 * vA * vB);
     double discriminant = sqrt(b * b - 4 * a * c);
     double root = (-b + discriminant)/(2 * a);
     //only one of the roots is the solution, the other pertains to the current velocities
     if (root - vB < 0.01) {
       root = (-b - discriminant)/(2 * a);
     }


     //The resulting changes in velocity for ball A and B
     ChangeInPoolGame changeFromB1 = b1->changeVelocity(mR * (vB - root) * collisionVector);
     ChangeInPoolGame changeFromB2 = b2->changeVelocity((root - vB) * collisionVector);
     QSoundEffect* s = m_soundPool->acquireSound("ball");
     if (s == nullptr) {
         m_soundPool->releaseSound(s);
         return changeFromB1.merge(changeFromB2);
     } else {
        s->play();
     }
     m_soundPool->releaseSound(s);
     return changeFromB1.merge(changeFromB2);
}

void Stage3Game::setSoundPool(SoundObjectPool *pool)  {
    m_soundPool = pool;
    dynamic_cast<Stage2Table*>(m_table)->setSoundPool(pool);
}
