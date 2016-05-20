#ifndef PULLEYJOINT_H
#define PULLEYJOINT_H

#include "Joint.h"

class PulleyJoint : public Joint
{
    Q_OBJECT
    Q_PROPERTY(QVector2D groundA READ getGroundA WRITE setGroundA)
    Q_PROPERTY(QVector2D groundB READ getGroundB WRITE setGroundB)
    Q_PROPERTY(qreal ratio READ getRatio WRITE setRatio)

    b2PulleyJointDef m_definition;
    QVector2D m_groundA;
    QVector2D m_groundB;
    qreal m_ratio;

public:

QVector2D getGroundA() const;

QVector2D getGroundB() const;

qreal getRatio() const;

public slots:
void setGroundA(QVector2D groundA);

void setGroundB(QVector2D groundB);

void setRatio(qreal ratio);

protected:
    virtual void linkBodies() override;
};

#endif // PULLEYJOINT_H
