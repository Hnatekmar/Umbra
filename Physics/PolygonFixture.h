#ifndef POLYGON_H
#define POLYGON_H

#include "Fixture.h"
#include <QPoint>
#include <QVariantList>

class PolygonFixture : public Fixture
{
    Q_OBJECT
    Q_PROPERTY(QVariantList points READ getPoints WRITE setPoints) // Body ze kterých se polygon skládá
public:
    explicit PolygonFixture(Fixture* parent = 0);
    virtual b2Shape* getShape() override;

    QVariantList getPoints() const
    {
        return m_points;
    }

public slots:
    void setPoints(QVariantList points)
    {
        m_points = points;
    }

private:
    b2Vec2* getVertices();
    QVariantList m_points;
};

#endif // POLYGON_H
