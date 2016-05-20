#include "FrictionJoint.h"

void FrictionJoint::linkBodies()
{
    if(m_bodyA == nullptr || m_bodyB == nullptr) return;
    WorldWrapper* world = m_bodyA->getWorld();
    if(m_joint)
    {
        world->getWorld()->DestroyJoint(m_joint);
        m_joint = nullptr;
    }

    b2Vec2 point = m_bodyA->getBody()->GetLocalCenter();

    m_definition.localAnchorA.Set(0.0f, 0.0f);
    m_definition.localAnchorB.Set(0.0f, 0.0f);

    m_definition.Initialize(m_bodyA->getBody(),
                            m_bodyB->getBody(),
                            point);

    m_joint = static_cast<b2Joint*>(world->getWorld()->CreateJoint(&m_definition));
}
