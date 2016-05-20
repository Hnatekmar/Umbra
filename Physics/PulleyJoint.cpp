#include "PulleyJoint.h"

QVector2D PulleyJoint::getGroundA() const
{
    return m_groundA;
}

QVector2D PulleyJoint::getGroundB() const
{
    return m_groundB;
}

qreal PulleyJoint::getRatio() const
{
    return m_ratio;
}

void PulleyJoint::setGroundA(QVector2D groundA)
{
    m_groundA = groundA;
    linkBodies();
}

void PulleyJoint::setGroundB(QVector2D groundB)
{
    m_groundB = groundB;
    linkBodies();
}

void PulleyJoint::setRatio(qreal ratio)
{
    m_ratio = ratio;
    linkBodies();
}

void PulleyJoint::linkBodies()
{
    if(m_bodyA == nullptr || m_bodyB == nullptr) return;
    WorldWrapper* world = m_bodyA->getWorld();

    if(m_joint)
    {
        world->getWorld()->DestroyJoint(m_joint);
        m_joint = nullptr;
    }


    m_definition.Initialize(m_bodyA->getBody(),
                            m_bodyB->getBody(),
                            b2Vec2(m_groundA.x() / world->getPixelsPerMeter(), m_groundA.y() / world->getPixelsPerMeter()),
                            b2Vec2(m_groundB.x() / world->getPixelsPerMeter(), m_groundB.y() / world->getPixelsPerMeter()),
                            m_bodyA->getBody()->GetWorldCenter(),
                            m_bodyA->getBody()->GetWorldCenter(),
                            m_ratio);
    m_joint = static_cast<b2Joint*>(world->getWorld()->CreateJoint(&m_definition));
}
