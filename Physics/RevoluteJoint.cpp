#include "RevoluteJoint.h"

void RevoluteJoint::setMotorSpeed(qreal speed)
{
    if(m_joint)
    {
        static_cast<b2RevoluteJoint*>(m_joint)->SetMotorSpeed(speed);
    }
}

bool RevoluteJoint::getCollideConnected() const
{
    return m_definition.collideConnected;
}

void RevoluteJoint::setCollideConnected(bool collideConnected)
{
    if (m_definition.collideConnected == collideConnected)
        return;

    m_definition.collideConnected = collideConnected;
    emit collideConnectedChanged(collideConnected);
}

void RevoluteJoint::linkBodies()
{
    if(m_bodyA == nullptr || m_bodyB == nullptr) return;
    WorldWrapper* world = m_bodyA->getWorld();
    if(m_joint)
    {
        world->getWorld()->DestroyJoint(m_joint);
        m_joint = nullptr;
    }

    b2Vec2 centerPoint = m_bodyA->getBody()->GetPosition();

    QPointF bodyACenter = QPointF(centerPoint.x * world->getPixelsPerMeter(), -centerPoint.y * world->getPixelsPerMeter());
    m_bodyB->setPosition(bodyACenter);
    m_definition.Initialize(m_bodyA->getBody(),
                            m_bodyB->getBody(),
                            centerPoint);

    m_joint = static_cast<b2Joint*>(world->getWorld()->CreateJoint(&m_definition));
}
