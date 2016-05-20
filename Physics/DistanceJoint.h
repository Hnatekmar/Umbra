#ifndef DISTANCEJOINT_H
#define DISTANCEJOINT_H

#include "Joint.h"

class DistanceJoint : public Joint
{
    Q_OBJECT
    Q_PROPERTY(qreal distance READ getDistance WRITE setDistance)
    Q_PROPERTY(bool collideConnected READ getCollideconnect WRITE setCollideConnect)
    Q_PROPERTY(qreal frequency READ getFrequency WRITE setFrequency)
    Q_PROPERTY(qreal dampingRatio READ getDampingRation WRITE setDampingRatio)
    Q_PROPERTY(QVector2D joiningPointA READ getJoiningPointA WRITE setJoiningPointA)
    Q_PROPERTY(QVector2D joiningPointB READ getJoiningPointB WRITE setJoiningPointB)

    b2DistanceJointDef m_definition;
    qreal m_distance;
    QVector2D m_joiningPointA;
    QVector2D m_joiningPointB;

public:

    qreal getDistance() const;

    bool getCollideconnect() const;

    qreal getFrequency() const;

    qreal getDampingRation() const;

    QVector2D getJoiningPointA() const;

    QVector2D getJoiningPointB() const;

    public slots:

    void setDistance(qreal distance);

    void setCollideConnect(bool collideConnected);

    void setFrequency(qreal frequency);

    void setDampingRatio(qreal dampingRatio);

    void setJoiningPointA(QVector2D joiningPointA);

    void setJoiningPointB(QVector2D joiningPointB);

protected:
    virtual void linkBodies() override;
};

#endif // DISTANCEJOINT_H
