#include "poolgame.h"
#include "cueballdecorator.h"
#include "stage2ball.h"
#include "duplicationballdecorator.h"
#include <iostream>


void PoolGame::simulateTimeStep(float timeStep)
{
    ChangeInPoolGame totalChange;
    //collisions of balls with the edge of the table
    for(Ball * b: m_balls)
    {
        totalChange = totalChange.merge(m_table->ballCollision(b));
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

void PoolGame::draw(QPainter &p)
{
    m_table->draw(p);
    for(Ball * b: m_balls)
    {
        b->draw(p);
    }
}

ChangeInPoolGame PoolGame::collide(Ball *b1, Ball *b2)
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
     return changeFromB1.merge(changeFromB2);
}

PoolGameMomento* PoolGame::createMomento() {
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

void PoolGame::setState(PoolGameMomento* m) {
    m_balls = m->getBalls();
    m_table = m->getTable();
}

void PoolGame::setCaretaker(Caretaker *c) {
    m_caretaker = c;
}

void PoolGame::rollback() {
    if (m_caretaker->canRollback()) {
        setState(m_caretaker->popMemento());
    } else {
        std::cout << "Cannot roll back" << std::endl;
    }
    for(Ball* b: m_balls) {
        b->setCopy(false);
    }
}

void PoolGame::randomBall() {
    Stage2Ball* ball;

    if(rand()%2==0) {
        CompositeBall* temp = new CompositeBall();
        temp->setCopy(false);
        temp->setMass(rand() % 50+1);
        temp->setPosition(QVector2D(rand() % int(m_table->width() - 5) + 5, rand() % int(m_table->height() - 5) + 5));
        temp->setRadius(rand() % 20 + 5);
        temp->setStrength(rand() % 10000000+1000);
        if(rand()%5==0) {
            temp->setStrength(std::numeric_limits<double>::infinity());
        }
        temp->setVelocity(QVector2D(rand()%200-100,rand()%200-100));
        temp->setColour(QColor(rand()%255, rand()%255, rand()%255));
        for(int i = 0; i < rand()%4+1; i++) {
            temp->addBall(randomCompositeHelper(temp->radius(), temp->position()));
        }
        ball = temp;
    } else {
        SimpleStage2Ball* temp = new SimpleStage2Ball();
        temp->setCopy(false);
        temp->setMass(rand() % 50+1);
        temp->setPosition(QVector2D(rand() % int(m_table->width() - 5) + 5, rand() % int(m_table->height() - 5) + 5));
        temp->setRadius(rand() % 20 + 5);
        temp->setStrength(rand() % 10000000+1000);
        if(rand()%5==0) {
            temp->setStrength(std::numeric_limits<double>::infinity());
        }
        temp->setVelocity(QVector2D(rand()%200-100,rand()%200-100));
        temp->setColour(QColor(rand()%255, rand()%255, rand()%255));
        ball = temp;
    }
    if(rand()%20==0){
        DuplicationBallDecorator* b = new DuplicationBallDecorator(ball);
        m_balls.push_back(b);
        return;
    }
    m_balls.push_back(ball);
}

Ball* PoolGame::randomCompositeHelper(float parentRadius, QVector2D parentPosition) {
    Ball* ball;

    if(rand()%10==0) {
        CompositeBall* temp = new CompositeBall();
        temp->setCopy(false);
        temp->setMass(rand() % 50+1);
        temp->setPosition(QVector2D(rand() % int(parentRadius - 5)*2 - int(parentRadius - 5), rand() % int(parentRadius - 5)*2 - int(parentRadius - 5)));
        temp->setRadius(rand() % (int(parentRadius-5)+1)+5);
        temp->setStrength(rand() % 10000000+1000);
        if(rand()%5==0) {
            temp->setStrength(std::numeric_limits<double>::infinity());
        }
        temp->setVelocity(QVector2D(rand()%200-100,rand()%200-100));
        temp->setColour(QColor(rand()%255, rand()%255, rand()%255));
        for(int i = 0; i < rand()%4+1; i++) {
            temp->addBall(randomCompositeHelper(temp->radius(), temp->position()));
        }
        ball = temp;
    } else {
        SimpleStage2Ball* temp = new SimpleStage2Ball();
        temp->setCopy(false);
        temp->setMass(rand() % 50+1);
        temp->setPosition(QVector2D(rand() % int(parentRadius - 5)*2 - int(parentRadius - 5), rand() % int(parentRadius - 5)*2 - int(parentRadius - 5)));
        temp->setRadius(rand() % (int(parentRadius-5)+1)+5);
        temp->setStrength(rand() % 10000000+1000);
        if(rand()%5==0) {
            temp->setStrength(std::numeric_limits<double>::infinity());
        }
        temp->setVelocity(QVector2D(rand()%200-100,rand()%200-100));
        temp->setColour(QColor(rand()%255, rand()%255, rand()%255));
        ball = temp;
    }

    return ball;
}
