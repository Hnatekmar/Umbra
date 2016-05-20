#ifndef JOINT_H
#define JOINT_H

#include <QObject>
#include "PhysicEntity.h"

/**
 * @brief Bázová třída popisující kloub
 */
class Joint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PhysicEntity* bodyA READ getBodyA WRITE setBodyA NOTIFY bodyAChanged)
    Q_PROPERTY(PhysicEntity* bodyB READ getBodyB WRITE setBodyB NOTIFY bodyBChanged)
    Q_PROPERTY(QPoint pointA READ getPointA WRITE setPointA NOTIFY pointAChanged) // Lokální offset vůči středu tělesa A
    Q_PROPERTY(QPoint pointB READ getPointB WRITE setPointB NOTIFY pointBChanged) // Lokální offset vůči středu tělesa B

protected:
    QPoint m_pointA;
    QPoint m_pointB;
    PhysicEntity* m_bodyA;
    PhysicEntity* m_bodyB;
    b2Joint* m_joint;

    /**
     * @brief Propojí 2 těla mezi sebou
     */
    virtual void linkBodies() = 0;

public:
    explicit Joint(QObject *parent = 0);
    PhysicEntity* getBodyA() const;
    PhysicEntity* getBodyB() const;

signals:
    void bodyAChanged(PhysicEntity* bodyA);
    void bodyBChanged(PhysicEntity* bodyB);
    void pointAChanged(QPoint pointA);
    void pointBChanged(QPoint pointB);

public slots:
    void setBodyA(PhysicEntity* bodyA);
    void setBodyB(PhysicEntity* bodyB);
    void setPointA(QPoint pointA);
    void setPointB(QPoint pointB);

public:
    QPoint getPointA() const;
    QPoint getPointB() const;
};

#endif // JOINT_H
