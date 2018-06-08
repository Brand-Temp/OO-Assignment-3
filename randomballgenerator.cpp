#include "randomballgenerator.h"

RandomBallGenerator::RandomBallGenerator()
{

}

Ball* RandomBallGenerator::getBall(int twidth, int theight) {
    Stage2Ball* ball;

    if(rand()%2==0) {
        CompositeBall* temp = new CompositeBall();
        temp->setCopy(false);
        temp->setMass(rand() % 50+1);
        temp->setPosition(QVector2D(rand() % int(twidth - 5) + 5, rand() % int(theight - 5) + 5));
        temp->setRadius(rand() % 20 + 5);
        temp->setStrength(rand() % 10000000+1000);
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
        temp->setPosition(QVector2D(rand() % int(twidth - 5) + 5, rand() % int(theight - 5) + 5));
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
        return b;
    }
    return ball;
}

Ball* RandomBallGenerator::randomCompositeHelper(float parentRadius, QVector2D parentPosition) {
    Ball* ball;

    if(rand()%10==0) {
        CompositeBall* temp = new CompositeBall();
        temp->setCopy(false);
        temp->setMass(rand() % 50+1);
        temp->setPosition(QVector2D(rand() % int(parentRadius - 5)*2 - int(parentRadius - 5), rand() % int(parentRadius - 5)*2 - int(parentRadius - 5)));
        temp->setRadius(rand() % (int(parentRadius-5)+1)+5);
        temp->setStrength(rand() % 10000000+1000);
        temp->setVelocity(QVector2D(rand()%200-100,rand()%200-100));
        temp->setColour(QColor(rand()%255, rand()%255, rand()%255));
        for(int i = 0; i < rand()%4+1; i++) {
            temp->addBall(randomCompositeHelper(temp->radius(), temp->position()));
        }
        // reposition ball to ensure it is fully enclose:
        if(temp->position().x() + temp->radius() + parentPosition.x() > parentPosition.x()+parentRadius) {
            int difference = (temp->position().x() + temp->radius() + parentPosition.x()) - (parentPosition.x()+parentRadius);
            difference++;
            temp->changePosition(QVector2D(-difference, 0));
        }
        if(temp->position().x() - temp->radius() + parentPosition.x() < parentPosition.x() - parentRadius) {
            int difference = (temp->position().x() - temp->radius() + parentPosition.x()) - (parentPosition.x()-parentRadius);
            difference--;
            temp->changePosition(QVector2D(-difference, 0));
        }
        if(temp->position().y() + temp->radius() + parentPosition.y() > parentPosition.y()+parentRadius) {
            int difference = (temp->position().y() + temp->radius() + parentPosition.y()) - (parentPosition.y()+parentRadius);
            difference++;
            temp->changePosition(QVector2D(0, -difference));
        }
        if(temp->position().y() - temp->radius() + parentPosition.y() < parentPosition.y() - parentRadius) {
            int difference = (temp->position().y() - temp->radius() + parentPosition.y()) - (parentPosition.y()-parentRadius);
            difference--;
            temp->changePosition(QVector2D(0, -difference));
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
        // reposition ball to ensure it is fully enclose:
        if(temp->position().x() + temp->radius() + parentPosition.x() > parentPosition.x()+parentRadius) {
            int difference = (temp->position().x() + temp->radius() + parentPosition.x()) - (parentPosition.x()+parentRadius);
            difference++;
            temp->changePosition(QVector2D(-difference, 0));
        }
        if(temp->position().x() - temp->radius() + parentPosition.x() < parentPosition.x() - parentRadius) {
            int difference = (temp->position().x() - temp->radius() + parentPosition.x()) - (parentPosition.x()-parentRadius);
            difference--;
            temp->changePosition(QVector2D(-difference, 0));
        }
        if(temp->position().y() + temp->radius() + parentPosition.y() > parentPosition.y()+parentRadius) {
            int difference = (temp->position().y() + temp->radius() + parentPosition.y()) - (parentPosition.y()+parentRadius);
            difference++;
            temp->changePosition(QVector2D(0, -difference));
        }
        if(temp->position().y() - temp->radius() + parentPosition.y() < parentPosition.y() - parentRadius) {
            int difference = (temp->position().y() - temp->radius() + parentPosition.y()) - (parentPosition.y()-parentRadius);
            difference--;
            temp->changePosition(QVector2D(0, -difference));
        }
        ball = temp;
    }

    return ball;
}
