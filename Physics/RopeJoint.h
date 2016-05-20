#ifndef ROPEJOINT_H
#define ROPEJOINT_H

#include "Joint.h"

class RopeJoint : public Joint
{
    Q_OBJECT
    b2RopeJointDef m_definition;
public:

    // Joint interface
protected:
    virtual void linkBodies() override;
};

#endif // ROPEJOINT_H
