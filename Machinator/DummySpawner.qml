import QtQuick 2.0
import Umbra 1.0

Entity {
    property double sinceLastSpawn : 0.0
    property var spawnedItem : Qt.createComponent(gui.selected + ".qml")
    property Layer target: parent
    property bool canSpawn: true

    signal entityClicked(PhysicEntity entity)

    function onClicked(entity)
    {
        entityClicked(entity)
    }

    function tick(delta)
    {
        var mousePos = game.getMousePos()
        x = mousePos.x
        y = mousePos.y
        sinceLastSpawn += delta
        if(!game.isLeftMouseButtonPressed())
        {
            canSpawn = true
        }
        if(game.isLeftMouseButtonPressed() && sinceLastSpawn > 0.5 && y < window.height - gui.height)
        {
            spawn()
            sinceLastSpawn = 0.0
        }
        if(game.isPressed(Qt.Key_Escape))
        {
            game.currentScene = 0
        }
    }

    function spawn()
    {
        if(spawnedItem.status === Component.Ready && canSpawn)
        {
            spawnedItem.createObject(target,
                                     {
                                         "x" : -myLayer.x + x,
                                         "y" : -myLayer.y + y,
                                     })
            canSpawn = false
        }
    }
}
