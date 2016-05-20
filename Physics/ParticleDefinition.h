#ifndef PARParticleFlagICLEDEFINIParticleFlagION_H
#define PARParticleFlagICLEDEFINIParticleFlagION_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <Box2D/Box2D.h>
#include <QQuickWindow>
#include <QVariantList>
#include  "../Entity.h"
#include "WorldWrapper.h"

/**
 * @brief Třída reprezentující vlastnost částic (obal pro enumeraci)
 */
class ParticleFlag : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ParticleType flag READ getFlag WRITE setFlag)

    uint32 m_flag;
public:

    explicit ParticleFlag(QObject* parent = 0);

    enum ParticleType
    {
        SOLID = b2_solidParticleGroup,
        RIGID = b2_rigidParticleGroup,
        ELASTIC = b2_elasticParticle,
        POWDER = b2_powderParticle,
        SPRING = b2_springParticle,
        TENSILE = b2_tensileParticle,
        VISCOUS = b2_viscousParticle,
        STATIC_PRESSURE = b2_staticPressureParticle,
        WALL = b2_wallParticle,
        BARRIER = b2_barrierParticle,
        ZOMBIE = b2_zombieParticle,
        COLOR_MIXING = b2_colorMixingParticle
    };
    Q_ENUM(ParticleType)

    ParticleType getFlag() const;
public slots:
    void setFlag(ParticleType flag);
};

/**
 * @brief Třída reprezentující definici vlastností částic
 */
class ParticleDefinition : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged) // Barva částic
    Q_PROPERTY(QQmlListProperty<ParticleFlag> flags READ getFlags) // Vlastnosti částic
    Q_PROPERTY(qreal lifetime READ getLifetime WRITE setLifetime) // Životnost částic
    Q_PROPERTY(qreal strength READ getStrength WRITE setStrength NOTIFY strengthChanged) // Kohéze částic

public:

    explicit ParticleDefinition(QQuickItem *parent = 0);

    void setColor(const QColor& color);
    QColor getColor() const;


    const b2ParticleDef& getParticleDef() const;

    const b2ParticleGroupDef& getParticleGroupDef() const;


private:
    b2ParticleSystemDef m_particleSystemDef;
    b2ParticleGroupDef m_particleGroupDef;
    void setParticleFlag(const ParticleFlag::ParticleType& flag);

    QList<ParticleFlag*> m_flags;

    qreal m_strength;

signals:
    void colorChanged();

    void strengthChanged(qreal strength);

public:
    virtual void componentComplete() override;

    /**
     * @brief Metoda, která se zavolá při přidání vlastnosti
     * @param property - pole
     * @param value - hodnota
     */
    static void addFlag(QQmlListProperty<ParticleFlag> *property, ParticleFlag *value);
    /**
     * @brief Zavolá se při ziskání elementu z pole
     * @param property - pole
     * @param index - pozice v poli
     * @return vlastnost
     */
    static ParticleFlag *atFlag(QQmlListProperty<ParticleFlag> *property, int index);
    /**
     * @brief Čistí pole
     * @param pole
     */
    static void clearFlag(QQmlListProperty<ParticleFlag> *property);
    /**
     * @brief Vrátí počet položek v poli
     * @param pole
     * @return počet položek
     */
    static int countFlag(QQmlListProperty<ParticleFlag> *property);

    /**
     * @brief Vymaže všechny vlastnosti
     */
    void resetFlags();

    QQmlListProperty<ParticleFlag> getFlags();
    qreal getLifetime() const;
    qreal getStrength() const;

public slots:
    void setLifetime(qreal lifetime);
    void setStrength(qreal strength);
};
#endif // PARParticleFlagICLEDEFINIParticleFlagION_H
