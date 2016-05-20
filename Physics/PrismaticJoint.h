#ifndef PRISMATICJOINT_H
#define PRISMATICJOINT_H

#include "Joint.h"

class PrismaticJoint : public Joint
{
    Q_OBJECT
    Q_PROPERTY(QVector2D axis READ getAxis WRITE setAxis)
    b2PrismaticJointDef m_definition;
    QVector2D m_axis;

public:
    QVector2D getAxis() const
    {
        return m_axis;
    }

public slots:
    void setAxis(QVector2D axis);

protected:
    virtual void linkBodies() override;
};

#endif // PRISMATICJOINT_H
