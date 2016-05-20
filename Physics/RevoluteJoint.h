#ifndef REVOLUTEJOINT_H
#define REVOLUTEJOINT_H

#include "Joint.h"

class RevoluteJoint : public Joint
{
    Q_OBJECT
    Q_PROPERTY(bool collideConnected READ getCollideConnected WRITE setCollideConnected NOTIFY collideConnectedChanged)
    b2RevoluteJointDef m_definition;

public:
    Q_INVOKABLE void setMotorSpeed(qreal speed);
    bool getCollideConnected() const;

public:
    void setCollideConnected(bool collideConnected);

signals:
    void collideConnectedChanged(bool collideConnected);

protected:
    virtual void linkBodies() override;
};

#endif // REVOLUTEJOINT_H
