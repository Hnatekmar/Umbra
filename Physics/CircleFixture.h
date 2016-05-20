#ifndef CIRCLE_H
#define CIRCLE_H

#include "Fixture.h"

class CircleFixture : public Fixture
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ getRadius WRITE setRadius) // Specifikuje poloměr kruhu
public:
    explicit CircleFixture(Fixture* parent = 0);
    b2Shape *getShape();

    qreal getRadius() const;
    void setRadius(const qreal &radius);

private:
    qreal m_radius;
};

#endif // CIRCLE_H
