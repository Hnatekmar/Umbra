#ifndef GEARJOINT_H
#define GEARJOINT_H

#include "Joint.h"

class GearJoint : public Joint
{
    Q_OBJECT
    Q_PROPERTY(qreal ratio READ getRatio WRITE setRatio)
    b2GearJointDef m_definition;
    qreal m_ratio;

public:

qreal getRatio() const
{
    return m_ratio;
}

public slots:
void setRatio(qreal ratio)
{
    m_ratio = ratio;
    linkBodies();
}

protected:
    virtual void linkBodies() override;
};

#endif // GEARJOINT_H
