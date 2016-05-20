#ifndef LAYER_H
#define LAYER_H

#include "EntityManager.h"
#include "Physics/PhysicEntity.h"
#include "Physics/ParticleDefinition.h"
#include <QQuickItem>
#include <QList>
#include <QSGGeometryNode>
#include <QSGTextureProvider>

/**
 * @brief Třída reprezentující výsledek raycastingu
 */
class RaycastResult : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PhysicEntity* entity READ getEntity) // Entita, která byla zasažena
    Q_PROPERTY(QPointF hitPoint READ getHitPoint) // Pozice zásahu

    PhysicEntity* m_entity;
    QPointF m_hitPoint;

public:

    void setEntity(PhysicEntity* entity)
    {
        m_entity = entity;
    }

    void setHitPoint(const QPointF& hitPoint)
    {
        m_hitPoint = hitPoint;
    }

    PhysicEntity* getEntity() const
    {
        return m_entity;
    }

    QPointF getHitPoint() const
    {
        return m_hitPoint;
    }
};

class Layer : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal gravitationX READ getGravX WRITE setGravX)
    Q_PROPERTY(qreal gravitationY READ getGravY WRITE setGravY)
    Q_PROPERTY(qint32 maximumParticleCount READ getMaximumParticleCount WRITE setMaximumParticleCount)

    /**
     * @brief Třída, která vrátí nejbližší možný objekt, který protíná paprsek při raycastingu
     */
    class NearestCallback : public b2RayCastCallback
    {
    public:
        float32 m_fraction;
        b2Fixture* m_fixture = nullptr;
        b2Vec2 m_normal, m_point;
        float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override
        {
            if(fixture->IsSensor())
            {
                return -1;
            }
            m_fixture = fixture;
            m_point = point;
            m_normal = normal;
            m_fraction = fraction;
            return fraction;
        }
    };

public:
    explicit Layer(QQuickItem* parent = 0);

    /**
     * @brief Updatne všechny entity, které jsou buď označené jako "chunkloaded" nebo jsou
     * @param pos
     * @param maxDepth
     */
    void think(int delta);

    qreal getGravX();
    qreal getGravY();
    void setGravX(const qreal& x);
    void setGravY(const qreal& y);

    /**
     * @brief Vyšle do světa paprsek a vráti informace o nárazu
     * @return výsledek nárazu
     */
    Q_INVOKABLE RaycastResult* raycast(QPointF start, QPointF end);

    /**
     * @brief Zastaví obnovování vrstvy
     */
    Q_INVOKABLE void pause();

    /**
     * @brief Obnoví obnovování vrstvy, pokudy byla zastavená
     */
    Q_INVOKABLE void unPause();

    /**
     * @brief Vytvoří obdelník danné velikosti složený z částic
     * @param box - definice obdelníka
     * @param definition - definice částic
     */
    Q_INVOKABLE void createParticleBox(const QRect& box, ParticleDefinition* definition);
    /**
     * @brief Vytvoří obdelník danné velikosti složený z částic pod určitým úhlem.
     * @param box - definice obdelníka
     * @param definition - definice částic
     * @param angle - úhel
     */
    Q_INVOKABLE void createParticleBox(const QRect& box, ParticleDefinition* definition, qreal angle);

    /**
     * @brief Vytvoří kruh danné velikosti složený z částic pod určitým úhlem.
     * @param position - pozice
     * @param radius - poloměr
     * @param definition - definice částic
     */
    Q_INVOKABLE void createParticleCircle(const QPoint& position, qreal radius, ParticleDefinition* definition);


    /**
     * @brief Najde všechny entity v oblasti ohraničené obdelníkem
     * @param rect - Obdelník ve kterém se mají entity hledat
     * @return list entit
     */
    Q_INVOKABLE QList<QObject*> getEntitiesInRect(const QRectF &rect);

private:
    void handleAddedItem(QQuickItem* item);
    virtual void itemChange(ItemChange change, const ItemChangeData& data) override;
    bool m_started;
    EntityManager m_entityManager;
    bool m_paused;
    b2ParticleSystem* m_particleSystem;

    // QQuickItem interface
    qint32 m_maximumParticleCount;

protected:
    virtual QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData) override;

    // QQmlParserStatus interface
public:
    virtual void componentComplete() override;
    qint32 getMaximumParticleCount() const;
public slots:
    void setMaximumParticleCount(qint32 maximumParticleCount);

};

#endif // LAYER_H
