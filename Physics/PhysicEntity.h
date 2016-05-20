#ifndef ISHAPE_H
#define ISHAPE_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <QVector2D>
#include <QPointer>
#include <vector>
#include <QPoint>
#include "../Entity.h"
#include "Fixture.h"
#include <functional>
#include "WorldWrapper.h"
#include <qmath.h>

class PhysicEntity : public Entity
{
    Q_OBJECT
    Q_PROPERTY(Fixture* fixture READ getFixture WRITE setFixture NOTIFY fixtureChanged)
    Q_PROPERTY(BodyType bodyType READ getBodyType WRITE setBodyType)
    Q_PROPERTY(bool isBullet READ getBullet WRITE setBullet)

    void registerFixture();
    QPointF toWorldPoint(const b2Vec2& point);

public:


    enum BodyType
    {
       STATIC = b2_staticBody,
       DYNAMIC = b2_dynamicBody,
       KINEMATIC = b2_kinematicBody
    };

    void setBullet(const bool bullet);
    bool getBullet()
    {
        return m_body->IsBullet();
    }


    Q_ENUMS(BodyType)
    void setBodyType(BodyType bodyType);
    BodyType getBodyType() const;

    explicit PhysicEntity(Entity *parent = 0);
    ~PhysicEntity();

    Q_INVOKABLE qreal getMass();

    Q_INVOKABLE void setAngularVelocity(qreal n)
    {
        m_body->SetAngularVelocity(n);
    }

    Fixture* getFixture()
    {
        return m_fixture;
    }

    void setFixture(Fixture* fixture);

    Q_INVOKABLE void applyAngularImpulse(qreal impulse);
    Q_INVOKABLE void applyTorque(qreal torque);
    Q_INVOKABLE void applyForce(const QVector2D& forceVec);
    Q_INVOKABLE void applyImpulse(const QVector2D& forceVec);
    Q_INVOKABLE void setLinearVelocity(const QVector2D& forceVec);

    void setWorld(WorldWrapper* world);
    WorldWrapper* getWorld();

    void setX(qreal x);
    void setY(qreal y);

    /**
     * @brief Zařídí, že na tomto tvaru nebude probíhat fyzikální simulace
     */
    void sleep();

    void unSleep();

    virtual void think(qreal delta) override;
    b2Body* getBody();

    QRectF getOffset();

signals:
    void fixtureChanged();
    void sensorContactStart(PhysicEntity* entity);
    void sensorContactEnd(PhysicEntity* entity);

private slots:
    void setRotation();
    void positionChanged();
    void componentComplete() override;

protected:
    /**
     * @brief Zaregistruje entitu do fyzikálního světa
     */
    void registerToWorld();

    b2Body* m_body;
    WorldWrapper* m_world;

    bool m_lock;

    Fixture* m_fixture;
    b2BodyDef m_bodyDefinition;
};

#endif // ISHAPE_H
