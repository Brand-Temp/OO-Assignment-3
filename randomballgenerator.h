#ifndef RANDOMBALLGENERATOR_H
#define RANDOMBALLGENERATOR_H
#include "stage2ball.h"
#include "duplicationballdecorator.h"

class RandomBallGenerator
{
public:
    RandomBallGenerator();

    /**
     * @brief getBall - generate a random ball and return a pointer to it
     */
    Ball* getBall(int twidth, int theight);

    /**
     * @brief randomCompositeHelper - helper function for making random inner balls on a composite;
     * @return a ball *
     */
    Ball* randomCompositeHelper(float parentRadius, QVector2D parentPosition);

};

#endif // RANDOMBALLGENERATOR_H
