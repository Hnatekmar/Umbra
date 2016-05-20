#include "Fixture.h"
#include <qmath.h>

Fixture::Fixture(QObject *parent) : QObject(parent),
                                    m_angle(0.0),
                                    m_width(1.0),
                                    m_height(1.0),
                                    m_world(nullptr),
                                    m_body(nullptr),
                                    m_fixture(nullptr)
{
}

void Fixture::registerToBody()
{
    if(m_body == nullptr || m_world == nullptr) return;
    if(m_fixture != nullptr) m_body->DestroyFixture(m_fixture);
    m_fixture = m_body->CreateFixture(getShape(), 1.0f);
}

qreal Fixture::getAngle() const
{
    return m_angle;
}

void Fixture::setAngle(const qreal &angle)
{
    if(m_angle != angle)
    {
        m_angle = angle;
        registerToBody();
        emit angleChanged();
    }
}

qreal Fixture::getWidth()
{
    return m_width;
}

qreal Fixture::getHeight()
{
    return m_height;
}

void Fixture::setWidth(const qreal& width)
{
    m_width = width;
    if(m_world && m_body)
    {
        registerToBody();
    }
    emit scaleChanged();
}

void Fixture::setHeight(const qreal &height)
{
    m_height = height;
    if(m_world && m_body)
    {
        registerToBody();
    }
    emit scaleChanged();
}

Fixture::~Fixture()
{
    m_body->DestroyFixture(m_fixture);
}

void Fixture::setFriction(qreal friction)
{
    if(!m_fixture) return;
    m_fixture->SetFriction(friction);
    emit frictionChanged();
}

qreal Fixture::getFriction() const
{
    return m_fixture->GetFriction();
}

void Fixture::setDensity(qreal density)
{
    if(!m_fixture) return;
    if(m_fixture->GetDensity() != density)
    {
        m_fixture->SetDensity(density);
        m_body->ResetMassData();
        emit densityChanged();
    }
}

qreal Fixture::getDensity() const
{
    return m_fixture->GetDensity();
}

bool Fixture::getSensor() const
{
    return m_fixture->IsSensor();
}

void Fixture::setSensor(bool sensor)
{
    if(!m_fixture) return;
    if(m_fixture->IsSensor() != sensor)
    {
        m_fixture->SetSensor(sensor);
        emit sensorChanged();
    }
}

void Fixture::setRestitution(qreal restitution)
{
    if(!m_fixture) return;
    m_fixture->SetRestitution(restitution);
    emit restitutionChanged();
}

qreal Fixture::getRestitution() const
{
    return m_fixture->GetRestitution();
}

void Fixture::setWorld(WorldWrapper *world)
{
    Q_ASSERT(world);
    m_world = world;
}

void Fixture::setBody(b2Body *body)
{
    Q_ASSERT(body);
    m_body = body;
}

