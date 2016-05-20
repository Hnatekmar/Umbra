#include "PhysicEntity.h"
#include <QDebug>
#include <qmath.h>

PhysicEntity::PhysicEntity(Entity *parent) : Entity(parent),
                                             m_body(nullptr),
                                             m_world(nullptr),
                                             m_lock(true),
                                             m_fixture(nullptr),
                                             m_bodyDefinition()

{
    setTransformOrigin(QQuickItem::Center);
    connect(this, SIGNAL(rotationChanged()), this, SLOT(setRotation()));
    connect(this, SIGNAL(xChanged()), this, SLOT(positionChanged()));
    connect(this, SIGNAL(yChanged()), this, SLOT(positionChanged()));
}

void PhysicEntity::registerFixture()
{
    m_fixture->setWorld(m_world);
    m_fixture->setBody(m_body);
    m_fixture->registerToBody();
    m_body->SetUserData(this);
}

QPointF PhysicEntity::toWorldPoint(const b2Vec2 &point)
{
    return QPointF(point.x * m_world->getPixelsPerMeter() - getOffset().width() / 2.0, -point.y * m_world->getPixelsPerMeter() - getOffset().height() / 2.0);
}

void PhysicEntity::setBullet(const bool bullet)
{
    m_body->SetBullet(bullet);
}

void PhysicEntity::setBodyType(BodyType bodyType)
{
    m_bodyDefinition.type = static_cast<b2BodyType>(bodyType);
    if(m_body != nullptr)
    {
        m_body->SetType(static_cast<b2BodyType>(bodyType));
    }
}

PhysicEntity::BodyType PhysicEntity::getBodyType() const
{
   return static_cast<BodyType>(m_body->GetType());
}

void PhysicEntity::setFixture(Fixture *fixture)
{
    Q_ASSERT(fixture != nullptr);
    if(m_fixture != nullptr)
    {
        delete m_fixture;
    }
    m_fixture = fixture;
    if(m_body && m_world) registerFixture();
    emit fixtureChanged();
}


void PhysicEntity::setWorld(WorldWrapper *world)
{
    m_world = world;
    registerToWorld();
}

WorldWrapper *PhysicEntity::getWorld()
{
    return m_world;
}

PhysicEntity::~PhysicEntity()
{
    m_body->GetFixtureList()->SetUserData(nullptr);
}

qreal PhysicEntity::getMass()
{
    Q_ASSERT(m_body);
    return m_body->GetMass();
}

void PhysicEntity::registerToWorld()
{
   Q_ASSERT(m_world);
   Q_ASSERT(m_fixture);
   m_body = m_world->getWorld()->CreateBody(&m_bodyDefinition);
   m_body->SetUserData(this);
   setBodyType(getBodyType());
}


void PhysicEntity::applyAngularImpulse(qreal impulse)
{
    Q_ASSERT(m_body != nullptr);
    m_body->ApplyAngularImpulse(impulse / m_world->getPixelsPerMeter(), true);
}

void PhysicEntity::applyTorque(qreal torque)
{
    Q_ASSERT(m_body != nullptr);
    m_body->ApplyTorque(torque, true);
}

void PhysicEntity::applyForce(const QVector2D &forceVec)
{
    Q_ASSERT(m_body != nullptr);
    m_body->ApplyForce(b2Vec2(forceVec.x() / m_world->getPixelsPerMeter(), forceVec.y() / m_world->getPixelsPerMeter()), m_body->GetWorldCenter(), true);
}

void PhysicEntity::applyImpulse(const QVector2D &forceVec)
{
    Q_ASSERT(m_body != nullptr);
    m_body->ApplyLinearImpulse(b2Vec2(forceVec.x() / m_world->getPixelsPerMeter(), forceVec.y() / m_world->getPixelsPerMeter()), m_body->GetWorldCenter(), true);
}

void PhysicEntity::setLinearVelocity(const QVector2D &forceVec)
{
    Q_ASSERT(m_body != nullptr);
    m_body->SetAwake(true);
    m_body->SetLinearVelocity(b2Vec2(forceVec.x() / m_world->getPixelsPerMeter(), forceVec.y() / m_world->getPixelsPerMeter()));
}

void PhysicEntity::sleep()
{
    Q_ASSERT(m_body != nullptr);
    m_body->SetAwake(false);
}

void PhysicEntity::unSleep()
{
    Q_ASSERT(m_body != nullptr);
    m_body->SetAwake(true);
}

void PhysicEntity::think(qreal delta)
{
    if(isComponentComplete())
    {
        Entity::think(delta);
        auto pos = m_body->GetPosition();
        if(m_body != nullptr && pos.IsValid())
        {
            m_lock = true;
            auto offset = getOffset();
            setSize(QSize(offset.width(), offset.height()));
            b2Vec2 pos = m_body->GetPosition();
            setPosition(toWorldPoint(pos)); //+ QPointF(offset.width() / 2, -offset.height() / 2));
            QQuickItem::setRotation(-(m_body->GetAngle() * 360.0) / (2 * M_PI));
            m_lock = false;
        }
    }
}

b2Body *PhysicEntity::getBody()
{
    return m_body;
}

QRectF PhysicEntity::getOffset()
{
    if(!m_fixture) return QRectF();
    return QRectF(0, 0, m_fixture->getWidth(), m_fixture->getHeight());
}

void PhysicEntity::positionChanged()
{
    if(!m_lock)
    {
        PhysicEntity::setX(x());
        PhysicEntity::setY(y());
    }
}

void PhysicEntity::componentComplete()
{
    m_bodyDefinition.angle = qRadiansToDegrees(rotation());
    PhysicEntity::setX(x());
    PhysicEntity::setY(y());
    registerFixture();
    m_body->SetSleepingAllowed(false);
    Entity::componentComplete();
}

void PhysicEntity::setX(qreal x)
{
    if(x != x) return;
    m_bodyDefinition.position.x = x / m_world->getPixelsPerMeter() + getOffset().width() / (m_world->getPixelsPerMeter() * 2.0); // x' = (w * k + x) / k
    if(m_body)
    {
        m_body->SetTransform(m_bodyDefinition.position,
                             m_bodyDefinition.angle);
    }
}

void PhysicEntity::setY(qreal y)
{
    if(y != y) return;
    m_bodyDefinition.position.y = -y / m_world->getPixelsPerMeter() - getOffset().height() / (m_world->getPixelsPerMeter() * 2.0);
    if(m_body)
    {
        m_body->SetTransform(m_bodyDefinition.position,
                             m_bodyDefinition.angle);
    }
}

void PhysicEntity::setRotation()
{
    if(m_lock) return;
    m_bodyDefinition.angle = -(rotation() * (M_PI * 2.0)) / 360;
    if(m_body)
    {
        m_body->SetTransform(m_body->GetPosition(), m_bodyDefinition.angle);
    }
}
