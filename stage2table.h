#ifndef STAGE2TABLE_H
#define STAGE2TABLE_H
#include <QColor>
#include <QPainter>
#include <vector>

#include "table.h"
#include "pocket.h"
#include "soundobjectpool.h"
/**
 * @brief The Stage2Table class is a concrete version of the Table class specific to stage one of the assignment
 */
class Stage2Table : public Table
{
public:
    Stage2Table(float width, float height,float friction, const QColor &colour, std::vector<Pocket*> pockets)
        :Table(width,height,friction),m_colour(colour),m_pockets(pockets)
    {}

    // Table interface
public:
    /**
     * @brief draw the table, it is just a rectangle of width() and height()
     * with the colour set in the constructor
     * @param p the painter used to draw the table
     */
    void draw(QPainter &p);

    void setSoundPool(SoundObjectPool* pool) {m_soundPool = pool;}

private:
    QColor m_colour;
    std::vector<Pocket*> m_pockets;
    SoundObjectPool* m_soundPool = nullptr;

    // Table interface
public:
    ChangeInPoolGame ballCollision(Ball *b);
};
#endif // STAGE2TABLE_H
