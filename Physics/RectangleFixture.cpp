#include "RectangleFixture.h"
#include <qmath.h>

RectangleFixture::RectangleFixture(Fixture *parent) : Fixture(parent)
{
}

b2Shape *RectangleFixture::getShape()
{
    b2PolygonShape* shape = new b2PolygonShape();
    shape->SetAsBox(m_width / (m_world->getPixelsPerMeter() * 2.0),
                    m_height / (m_world->getPixelsPerMeter() * 2.0),
                    b2Vec2(0, 0),
                    qDegreesToRadians(m_angle));
    return shape;
}



