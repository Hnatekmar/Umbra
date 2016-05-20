#include "Scene.h"

Scene::Scene(QQuickItem* parent) : QQuickItem(parent)
{
}

void Scene::think(int delta)
{
    QList<Layer*> layers = findChildren<Layer*>();
    for(Layer* layer : layers)
    {
        layer->think(delta);
    }
}
