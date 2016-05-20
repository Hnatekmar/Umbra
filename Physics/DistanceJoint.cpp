#include "DistanceJoint.h"

qreal DistanceJoint::getDistance() const
{
    return m_distance;
}

bool DistanceJoint::getCollideconnect() const
{
    return m_definition.collideConnected;
}

qreal DistanceJoint::getFrequency() const
{
    return m_definition.frequencyHz;
}

qreal DistanceJoint::getDampingRation() const
{
    return m_definition.dampingRatio;
}

QVector2D DistanceJoint::getJoiningPointA() const
{
    return m_joiningPointA;
}

QVector2D DistanceJoint::getJoiningPointB() const
{
    return m_joiningPointB;
}

void DistanceJoint::setDistance(qreal distance)
{
    m_distance = distance;
    linkBodies();
}

void DistanceJoint::setCollideConnect(bool collideConnected)
{
    m_definition.collideConnected = collideConnected;
    linkBodies();
}

void DistanceJoint::setFrequency(qreal frequency)
{
    m_definition.frequencyHz = frequency;
    linkBodies();
}

void DistanceJoint::setDampingRatio(qreal dampingRatio)
{
    m_definition.dampingRatio = dampingRatio;
    linkBodies();
}

void DistanceJoint::setJoiningPointA(QVector2D joiningPointA)
{
    m_joiningPointA = joiningPointA;
}

void DistanceJoint::setJoiningPointB(QVector2D joiningPointB)
{
    m_joiningPointB = joiningPointB;
}

void DistanceJoint::linkBodies()
{
    if(m_bodyA == nullptr || m_bodyB == nullptr) return;
    WorldWrapper* world = m_bodyA->getWorld();
    if(m_joint)
    {
        world->getWorld()->DestroyJoint(m_joint);
        m_joint = nullptr;
    }

    b2Vec2 pointA = m_bodyA->getBody()->GetLocalCenter();
    b2Vec2 pointB = m_bodyB->getBody()->GetLocalCenter();

    if(!m_joiningPointA.isNull())
    {
        pointA = b2Vec2(m_joiningPointA.x() / world->getPixelsPerMeter(),
                        m_joiningPointA.y() / world->getPixelsPerMeter());
    }

    if(!m_joiningPointB.isNull())
    {
        pointA = b2Vec2(m_joiningPointB.x() / world->getPixelsPerMeter(),
                        m_joiningPointB.y() / world->getPixelsPerMeter());
    }

    m_definition.Initialize(m_bodyA->getBody(),
                            m_bodyB->getBody(),
                            pointA,
                            pointB);
    m_definition.length = m_distance / world->getPixelsPerMeter();
    m_joint = static_cast<b2Joint*>(world->getWorld()->CreateJoint(&m_definition));
}
