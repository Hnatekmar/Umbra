#ifndef WELDJOINT_H
#define WELDJOINT_H

#include "Joint.h"

class WeldJoint : public Joint
{
    Q_OBJECT
    b2WeldJointDef m_definition;
public:

    // Joint interface
protected:
    virtual void linkBodies() override;
};

#endif // WELDJOINT_H
