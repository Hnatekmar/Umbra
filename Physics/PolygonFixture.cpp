#include "PolygonFixture.h"

PolygonFixture::PolygonFixture(Fixture *parent) : Fixture(parent),
                                    m_points()
{
}

b2Shape *PolygonFixture::getShape()
{
    b2PolygonShape* shape = new b2PolygonShape();
    shape->Set(getVertices(), m_points.count());
    return shape;
}

b2Vec2* PolygonFixture::getVertices()
{
    QRect boundingBox;
    b2Vec2* vertices = new b2Vec2[m_points.count()];
    for(int i = 0; i < m_points.count(); i++)
    {
        QPoint point = m_points.at(i).toPoint();
        if(!point.isNull())
        {
            boundingBox = boundingBox.intersected(QRect(std::max(0, point.x()),
                                                        0, point.x(), point.y()));
            vertices[i].Set(point.x() / m_world->getPixelsPerMeter(),
                            -point.y() / m_world->getPixelsPerMeter());
        }
    }
    m_width = boundingBox.width();
    m_height = boundingBox.height();
    return vertices;
}
