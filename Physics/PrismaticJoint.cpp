#include "PrismaticJoint.h"

void PrismaticJoint::setAxis(QVector2D axis)
{
    m_axis = axis;
    m_axis.normalize();
    linkBodies();
}

void PrismaticJoint::linkBodies()
{
    if(m_bodyA == nullptr || m_bodyB == nullptr) return;
    WorldWrapper* world = m_bodyA->getWorld();

    if(m_joint)
    {
        world->getWorld()->DestroyJoint(m_joint);
        m_joint = nullptr;
    }

    if(m_axis.isNull())
    {
        m_axis = QVector2D(1.0, 0.0);
    }

    b2Vec2 point = m_bodyA->getBody()->GetLocalCenter();

    m_definition.Initialize(m_bodyA->getBody(),
                            m_bodyB->getBody(),
                            point,
                            b2Vec2(m_axis.x(), m_axis.y()));
    m_joint = static_cast<b2Joint*>(world->getWorld()->CreateJoint(&m_definition));
}
