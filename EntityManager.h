#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QDebug>
#include <QMap>
#include <QPointer>
#include <QVector>
#include <exception>
#include <math.h>
#include <Box2D/Box2D.h>
#include "Physics/PhysicEntity.h"
#include <algorithm>
#include "Physics/WorldWrapper.h"

/**
  * class EntityManager
  */
class EntityManager
{
public:
  EntityManager();

  /**
   * @brief Přidá entitu do manažeru entit
   * @param entity - Entita, ktera má být přidaná
   */
  void add (Entity* entity);

  /**
   * @brief Najde všechny entity v oblasti ohraničené obdelníkem
   * @param rect - Obdelník ve kterém se mají entity hledat
   * @return list entit
   */
  QList<QObject *> getEntitiesInRect(const QRectF &rect);

  /**
   * @brief update
   */
  void update(int delta);

  /**
   * @brief Ziská entitu na základě její id
   * @return Hledaná entita
   * @param  id entity
   */
  const Entity* getByID (unsigned long id) const;

  /**
   * @param id - id entity, která má být odstraněna
   */
  void removeById (unsigned long id);

  /**
   * @brief vrátí box2D svět
   * @return box2D svět
   */
  WorldWrapper* getWorld();

private:

   void updateEntities(qreal delta);

   class Listener : public b2ContactListener
   {
       QVector<QPair<QPointer<PhysicEntity>, QPointer<PhysicEntity>>> m_contactStart;
       QVector<QPair<QPointer<PhysicEntity>, QPointer<PhysicEntity>>> m_contactEnd;

       inline void add(PhysicEntity* entityA, PhysicEntity* entityB, QVector<QPair<QPointer<PhysicEntity>, QPointer<PhysicEntity>>>& container)
       {
           container.push_back(qMakePair(QPointer<PhysicEntity>(entityA),
                                              QPointer<PhysicEntity>(entityB)));
       }
   public:
       virtual void BeginContact(b2Contact* contact) override
       {
           add(static_cast<PhysicEntity*>(contact->GetFixtureA()->GetBody()->GetUserData()),
               static_cast<PhysicEntity*>(contact->GetFixtureB()->GetBody()->GetUserData()), m_contactStart);
       }

       QVector<QPair<QPointer<PhysicEntity>, QPointer<PhysicEntity>>>& contactStarted()
       {
           return m_contactStart;
       }

       QVector<QPair<QPointer<PhysicEntity>, QPointer<PhysicEntity>>>& contactEnded()
       {
           return m_contactEnd;
       }

       virtual void EndContact(b2Contact* contact) override
       {
           add(static_cast<PhysicEntity*>(contact->GetFixtureA()->GetBody()->GetUserData()),
               static_cast<PhysicEntity*>(contact->GetFixtureB()->GetBody()->GetUserData()), m_contactEnd);
       }
   };

  float32 m_step = 25.0f / 1000.0f;
  Listener m_listener;
  double m_accumulator;
  WorldWrapper m_world;
  QVector<QPointer<Entity>> m_untrackedEntities;
  QVector<std::pair<std::pair<long, long>, unsigned long>> m_toBeRemoved;
  QVector<Entity*> m_toBeAdded;
};

#endif // ENTITYMANAGER_H
