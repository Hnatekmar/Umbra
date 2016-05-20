#include "GearJoint.h"

void GearJoint::linkBodies()
{
    if(m_bodyA == nullptr || m_bodyB == nullptr) return;
    WorldWrapper* world = m_bodyA->getWorld();

    if(m_joint)
    {
        world->getWorld()->DestroyJoint(m_joint);
        m_joint = nullptr;
    }

    /*b2Vec2 pointA = m_bodyA->getBody()->GetLocalCenter();
    b2Vec2 pointB = m_bodyB->getBody()->GetLocalCenter()*/;

    m_definition.ratio = m_ratio;
    m_definition.bodyA = m_bodyA->getBody();
    m_definition.bodyB = m_bodyB->getBody();

    m_joint = static_cast<b2Joint*>(world->getWorld()->CreateJoint(&m_definition));
}
