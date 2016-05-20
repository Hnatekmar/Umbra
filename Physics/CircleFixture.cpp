#include "CircleFixture.h"

CircleFixture::CircleFixture(Fixture *parent) : Fixture(parent)
{
}

b2Shape *CircleFixture::getShape()
{
    b2CircleShape* shape = new b2CircleShape();
    shape->m_radius = m_radius / m_world->getPixelsPerMeter();
    return shape;
}

qreal CircleFixture::getRadius() const
{
    return m_radius;
}

void CircleFixture::setRadius(const qreal &radius)
{
    m_radius = radius;
    m_width = radius * 2.0;
    m_height = radius * 2.0;
    registerToBody();
}
