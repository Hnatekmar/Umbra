#include "Joint.h"

Joint::Joint(QObject *parent) : QObject(parent),
                                m_pointA(),
                                m_pointB(),
                                m_bodyA(nullptr),
                                m_bodyB(nullptr),
                                m_joint(nullptr)
{
}

PhysicEntity *Joint::getBodyA() const
{
    return m_bodyA;
}

PhysicEntity *Joint::getBodyB() const
{
    return m_bodyB;
}

void Joint::setBodyA(PhysicEntity *bodyA)
{
    if (m_bodyA == bodyA)
        return;

    m_bodyA = bodyA;
    emit bodyAChanged(bodyA);
    if(m_bodyA != nullptr && m_bodyB != nullptr) linkBodies();
}

void Joint::setBodyB(PhysicEntity *bodyB)
{
    if (m_bodyB == bodyB)
        return;

    m_bodyB = bodyB;
    emit bodyBChanged(bodyB);
    if(m_bodyA != nullptr && m_bodyB != nullptr) linkBodies();
}

void Joint::setPointA(QPoint pointA)
{
    if (m_pointA == pointA)
        return;

    m_pointA = pointA;
    emit pointAChanged(pointA);
    linkBodies();
}

void Joint::setPointB(QPoint pointB)
{
    if (m_pointB == pointB)
        return;

    m_pointB = pointB;
    emit pointBChanged(pointB);
    linkBodies();
}

QPoint Joint::getPointA() const
{
    return m_pointA;
}

QPoint Joint::getPointB() const
{
    return m_pointB;
}

