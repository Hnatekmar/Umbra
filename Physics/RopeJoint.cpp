#include "RopeJoint.h"

void RopeJoint::linkBodies()
{
    if(m_bodyA == nullptr || m_bodyB == nullptr) return;
    WorldWrapper* world = m_bodyA->getWorld();
    if(m_joint)
    {
        world->getWorld()->DestroyJoint(m_joint);
        m_joint = nullptr;
    }


    m_definition.localAnchorA.Set(0.0f, 0.0f);
    m_definition.localAnchorB.Set(0.0f, 0.0f);

    m_joint = static_cast<b2Joint*>(world->getWorld()->CreateJoint(&m_definition));
}
