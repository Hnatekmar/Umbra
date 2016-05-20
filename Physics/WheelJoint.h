#ifndef WHEELJOINT_H
#define WHEELJOINT_H

#include "Joint.h"

class WheelJoint : public Joint
{
    Q_OBJECT
    Q_PROPERTY(QVector2D axis READ getAxis WRITE setAxis)
    b2WheelJointDef m_definition;
    QVector2D m_axis;

public:
    QVector2D getAxis() const;

public slots:
    void setAxis(QVector2D axis);

protected:
    virtual void linkBodies() override;
};

#endif // WHEELJOINT_H
