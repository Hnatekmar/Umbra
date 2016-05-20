#ifndef FIXTURE_H
#define FIXTURE_H

#include <QQuickItem>
#include <Box2D/Box2D.h>
#include "WorldWrapper.h"

class Fixture : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal friction READ getFriction WRITE setFriction NOTIFY frictionChanged())
    Q_PROPERTY(qreal density READ getDensity WRITE setDensity NOTIFY densityChanged())
    Q_PROPERTY(qreal restitution READ getRestitution WRITE setRestitution NOTIFY restitutionChanged())
    Q_PROPERTY(bool isSensor READ getSensor WRITE setSensor NOTIFY sensorChanged())
    Q_PROPERTY(qreal angle READ getAngle WRITE setAngle NOTIFY angleChanged)
public:

    /**
     * @brief Zaregistruje kloub do tělesa
     */
    void registerToBody();

    qreal getAngle() const;
    void setAngle(const qreal& angle);

    qreal getWidth();
    qreal getHeight();

    void setWidth(const qreal& width);
    void setHeight(const qreal& height);
    ~Fixture();

    void setFriction(qreal friction);
    qreal getFriction() const;

    void setDensity(qreal density);
    qreal getDensity() const;

    bool getSensor() const;
    void setSensor(bool sensor);

    void setRestitution(qreal restitution);
    qreal getRestitution() const;

    void setWorld(WorldWrapper* world);
    void setBody(b2Body* body);

    virtual b2Shape* getShape() = 0;

protected:
    qreal m_angle;
    explicit Fixture(QObject *parent = 0);
    qreal m_width;
    qreal m_height;
    WorldWrapper* m_world;
    b2Body* m_body;
    b2Fixture* m_fixture;

signals:
    void scaleChanged();
    void sensorChanged();
    void densityChanged();
    void frictionChanged();
    void restitutionChanged();
    void xChanged();
    void yChanged();
    void angleChanged();
};

#endif // FIXTURE_H
