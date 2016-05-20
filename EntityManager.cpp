#include "EntityManager.h"

EntityManager::EntityManager() :
    m_listener(),
    m_accumulator(0.0),
    m_world(new b2World(b2Vec2(0.0f, 0.0f)))
{
    m_world.getWorld()->SetContactListener(&m_listener);
}

void EntityManager::add(Entity* entity)
{
    m_untrackedEntities.append(entity);
}

QList<QObject *> EntityManager::getEntitiesInRect(const QRectF &rect)
{
    QList<QObject*> foundEntities;
    if(rect.isNull())
    {
        return foundEntities;
    }
    QPointer<Entity> entity;
    Q_FOREACH(entity, m_untrackedEntities)
    {
        if(entity != nullptr)
        {
            if(rect.contains(entity->position()))
            {
                foundEntities.append(entity);
            }
        }
    }
    return foundEntities;
}

const Entity *EntityManager::getByID(unsigned long id) const
{
    auto it = std::find_if(m_untrackedEntities.begin(), m_untrackedEntities.end(), [&id](Entity* en)
    {
       return en->getID() == id;
    });

    if(it != m_untrackedEntities.end())
    {
        return (*it);
    }
    return nullptr;
}

void EntityManager::updateEntities(qreal delta)
{
    QPointer<Entity> entity;
    Q_FOREACH(entity, m_untrackedEntities)
    {
        if(entity != nullptr)
        {
            entity->think(delta);
        }
    }
}

void EntityManager::removeById(unsigned long id)
{
    for(auto it = m_untrackedEntities.begin(); it != m_untrackedEntities.end(); it++)
    {
        if((*it)->getID() == id)
        {
            it = m_untrackedEntities.erase(it);
        }
    }
}

WorldWrapper* EntityManager::getWorld()
{
    return &m_world;
}

void EntityManager::update(int delta)
{
    m_accumulator += delta / 1000.0;

    while(m_accumulator >= m_step)
    {
        m_world.getWorld()->Step(m_step, 8, 3, 3);
        m_accumulator -= m_step;
    }

    updateEntities(delta / 1000.0);

    m_untrackedEntities.erase(std::remove_if(m_untrackedEntities.begin(), m_untrackedEntities.end(), [](const QPointer<Entity>& entity) {return entity == nullptr;}
    ), m_untrackedEntities.end());

    for(auto entity : m_toBeAdded)
    {
        add(entity);
    }

    m_toBeAdded.clear();

    auto hitList = m_listener.contactStarted();
    for(auto entity : hitList)
    {
        if(!entity.first.isNull() && !entity.second.isNull())
        {
            emit entity.first->sensorContactStart(entity.second);
            emit entity.second->sensorContactStart(entity.first);
        }
    }

    m_listener.contactStarted().clear();

    auto hitList2 = m_listener.contactEnded();
    for(auto entity : hitList2)
    {
        if(!entity.first.isNull() && !entity.second.isNull())
        {
            emit entity.first->sensorContactEnd(entity.second);
            emit entity.second->sensorContactEnd(entity.first);
        }
    }

    m_listener.contactEnded().clear();
}
