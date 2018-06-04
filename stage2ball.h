#ifndef STAGE2BALL_H
#define STAGE2BALL_H
#include <vector>

#include "ball.h"
#include "changeinpoolgame.h"

/**
 * @brief The Stage2Ball class is the component in the composite design pattern
 * it contains the general stage 2 quality strength
 */
class Stage2Ball : public Ball
{
public:
    Stage2Ball(){m_isCue = false; m_isComposite = false;}
    void setStrength(float strength){m_strength = strength;}
    // Ball interface
    void setCue() {
        m_isCue = true;
    }
    bool getCue() {return m_isCue;}
    bool isComposite() {return m_isComposite;}
    void setComposie(bool b) {m_isComposite = b;}
public:
    void draw(QPainter &p);

protected:
    float m_strength;
    bool m_isCue;
    bool m_isComposite;
};

/**
 * @brief The CompositeBall class is the composite in the composite design pattern,
 * it stores a vector of children of type Stage2Ball. It can break apart to release these balls.
 */
class CompositeBall : public Stage2Ball
{
public:
    CompositeBall():m_containedMass(0)
    {
        Ball::setRadius(-1);
        m_isComposite = true;
    }
    virtual ~CompositeBall();

    /**
     * @brief changeVelocity changes the velocity of the ball, if it changes to fast it may break apart
     * @param deltaV the change in velocity
     * @return the change to the poolgame list of balls, if the ball breaks it will be added to the remove list
     * and its children will be added to the add list
     */
    ChangeInPoolGame changeVelocity(const QVector2D &deltaV);

    /**
     * @brief mass get the total mass of the composite ball wich is the sum of its mass and the mass of its children
     * @return
     */
    float mass();

    /**
     * @brief draws the composite ball, if draw children is true it will also draw its children
     * @param p
     */
    void draw(QPainter &p);

    /**
     * @brief addBall to the composite
     * @param ball
     */
    void addBall(Ball* ball)
    {
        m_containedBalls.push_back(ball);
        m_containedMass += ball->mass();
    }

    /**
     * @brief setRadius sets the new radius of the ball, adjusting the radius of any children so they are stil contained
     * @param newRadius
     */
    void setRadius(float newRadius);

    Ball* copy();

protected:
    std::vector<Ball*> m_containedBalls;
    float m_containedMass;
    //here we decide whether or not to draw children
    bool drawChildren = true;
};

/**
 * @brief The SimpleStage2Ball class is the leaf in the composite design pattern,
 * all stage 2 balls that aren't composites are leaves
 */
class SimpleStage2Ball : public Stage2Ball
{
public:
    SimpleStage2Ball(){}
    SimpleStage2Ball(SimpleStage2Ball* other) {m_position = other->position();}
    ChangeInPoolGame changeVelocity(const QVector2D &deltaV);
    Ball* copy();

};

#endif // STAGE2BALL_H
