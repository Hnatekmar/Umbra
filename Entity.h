
#ifndef ENTITY_H
#define ENTITY_H

#include <QList>
#include <QVector2D>
#include <QQuickItem>
#include <QQmlExpression>
#include <QQuickWindow>
#include <algorithm>
#include <QQuickPaintedItem>

/**
  * class Entity
  * @brief Entita reprezentuje jakýkoliv objekt, který má pozici a chování. Jedná se tedy například o hráče.
  */
class Entity : public QQuickItem
{
        Q_OBJECT
public:

  explicit Entity(QQuickItem* parent = 0);

  /**
   * @return unsigned long - Unikátní id entity
   */
  Q_INVOKABLE unsigned long getID() const;

  /**
   * @brief Vrátí počet milisekund od posledního zavolání think
   * @see think
   * @return qreal - počet milisekund
   */
  Q_INVOKABLE qreal getDelta();

  /**
   * @brief volá funkci tick(delta) pokud v entitě existuje. Jestliže entita opustí obrazovku, tak vyvolá událost outOfScreen
   * @param delta - Počet milisekund od předchozího snímku podělených 1 000 000
   */
  virtual void think(qreal delta);

private:
  static unsigned long s_id;
  unsigned long m_id;
  qreal m_delta;
};

#endif // ENTITY_H
