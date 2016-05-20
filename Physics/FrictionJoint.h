#ifndef FRICTIONJOINT_H
#define FRICTIONJOINT_H

#include "Joint.h"

class FrictionJoint : public Joint
{
    Q_OBJECT
    b2FrictionJointDef m_definition;
public:

protected:
    virtual void linkBodies() override;
};

#endif // FRICTIONJOINT_H
