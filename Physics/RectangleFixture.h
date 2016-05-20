#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Fixture.h"

class RectangleFixture : public Fixture
{
    Q_OBJECT
    Q_PROPERTY(qreal width READ getWidth WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ getHeight WRITE setHeight NOTIFY heightChanged)

public:
    explicit RectangleFixture(Fixture* parent = 0);
virtual b2Shape* getShape();
qreal getWidth() const
{
    return m_width;
}

qreal getHeight() const
{
    return m_height;
}

public slots:
    void setWidth(qreal width)
    {
        Fixture::setWidth(width);
        emit widthChanged(width);
    }

    void setHeight(qreal height)
    {
        Fixture::setHeight(height);
        emit heightChanged(height);
    }

signals:
    void scaleChanged();
    void widthChanged(qreal width);
    void heightChanged(qreal height);
};

#endif // RECTANGLE_H
