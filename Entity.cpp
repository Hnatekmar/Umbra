#include "Entity.h"

unsigned long Entity::s_id = 0;

Entity::Entity(QQuickItem *parent): QQuickItem(parent),
                                           m_id(s_id++),
                                           m_delta(0.0)
{
}

/**
 * @return unsigned long
 */
unsigned long Entity::getID() const
{
    return m_id;
}

/**
 * @brief Vrátí počet milisekund od posledního zavolání think
 * @see think
 * @return int - počet milisekund
 */
qreal Entity::getDelta()
{
    return m_delta;
}

/**
 * @brief Zde se provádí logika entity
 */
void Entity::think(qreal delta)
{
    setWidth(childrenRect().width());
    setHeight(childrenRect().height());
    m_delta = delta;
    if(metaObject()->indexOfMethod("tick(QVariant)") != -1)
    {
        QVariant returnVal;
        QMetaObject::invokeMethod(this,
                                  "tick",
                                  Q_RETURN_ARG(QVariant, returnVal),
                                  Q_ARG(QVariant, delta));
    }
}

