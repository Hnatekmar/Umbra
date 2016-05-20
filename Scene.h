#ifndef SCENE_H
#define SCENE_H

#include "Layer.h"

/**
 * @brief The Scene class
 */
class Scene : public QQuickItem
{
    Q_OBJECT
public:
    explicit Scene(QQuickItem* parent = 0);

    /**
     * @brief Metoda, která se volá každý snímek hry
     * @param delta - rozdíl v čase
     */
    void think(int delta);
};

#endif // SCENE_H
