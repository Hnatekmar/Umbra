#include "ParticleDefinition.h"

ParticleDefinition::ParticleDefinition(QQuickItem *parent) : QQuickItem(parent),
                                                          m_particleSystemDef(),
                                                          m_particleGroupDef(),
                                                          m_flags()
{
    setLifetime(-1.0);
}

void ParticleDefinition::setColor(const QColor &color)
{
    m_particleGroupDef.color = b2Color(color.red() / 255.0f, color.green() / 255.0f, color.blue() / 255.0f);
}

QColor ParticleDefinition::getColor() const
{
    return QColor(m_particleGroupDef.color.r * 255, m_particleGroupDef.color.g * 255, m_particleGroupDef.color.b * 255);
}

const b2ParticleGroupDef &ParticleDefinition::getParticleGroupDef() const
{
    return m_particleGroupDef;
}

void ParticleDefinition::setParticleFlag(const ParticleFlag::ParticleType &flag)
{
    if(flag == ParticleFlag::SOLID || flag == ParticleFlag::RIGID)
    {
        m_particleGroupDef.groupFlags |= static_cast<uint32>(flag);
    }
    else
    {
        m_particleGroupDef.flags |= static_cast<uint32>(flag);
    }
}

void ParticleDefinition::componentComplete()
{
    QQuickItem::componentComplete();
}

ParticleFlag* ParticleDefinition::atFlag(QQmlListProperty<ParticleFlag> *property, int index)
{
    QList<ParticleFlag*>* data = static_cast<QList<ParticleFlag*>*>(property->data);
    return data->at(index);
}

void ParticleDefinition::clearFlag(QQmlListProperty<ParticleFlag> *property)
{
    QList<ParticleFlag*>* data = static_cast<QList<ParticleFlag*>*>(property->data);
    ParticleDefinition* definition = qobject_cast<ParticleDefinition*>(property->object);
    definition->resetFlags();
    data->clear();
}

int ParticleDefinition::countFlag(QQmlListProperty<ParticleFlag> *property)
{
    QList<ParticleFlag*>* data = static_cast<QList<ParticleFlag*>*>(property->data);
    return data->count();
}


void ParticleDefinition::addFlag(QQmlListProperty<ParticleFlag> *property, ParticleFlag *value)
{
    QList<ParticleFlag*>* data = static_cast<QList<ParticleFlag*>*>(property->data);
    data->append(value);
    ParticleDefinition* definition = qobject_cast<ParticleDefinition*>(property->object);
    definition->setParticleFlag(value->getFlag());
}

void ParticleDefinition::resetFlags()
{
    m_particleGroupDef.flags = 0;
}

QQmlListProperty<ParticleFlag> ParticleDefinition::getFlags()
{
    return QQmlListProperty<ParticleFlag>(this,
                                          &m_flags,
                                          &ParticleDefinition::addFlag,
                                          &ParticleDefinition::countFlag,
                                          &ParticleDefinition::atFlag,
                                          &ParticleDefinition::clearFlag);
}

qreal ParticleDefinition::getLifetime() const
{
    return m_particleGroupDef.lifetime;
}

qreal ParticleDefinition::getStrength() const
{
    return m_particleGroupDef.strength;
}

void ParticleDefinition::setLifetime(qreal lifetime)
{
    m_particleGroupDef.lifetime = lifetime;
}

void ParticleDefinition::setStrength(qreal strength)
{
    m_particleGroupDef.strength = strength;
    emit strengthChanged(strength);
}

ParticleFlag::ParticleFlag(QObject *parent) : QObject(parent)
{
}

ParticleFlag::ParticleType ParticleFlag::getFlag() const
{
    return static_cast<ParticleType>(m_flag);
}

void ParticleFlag::setFlag(ParticleFlag::ParticleType flag)
{
    m_flag = static_cast<uint32>(flag);
}
