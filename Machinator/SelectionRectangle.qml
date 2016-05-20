import QtQuick 2.0
import Umbra 1.0

Entity {

    Rectangle{
        id: selectionRectangle
        color: "transparent"
        border.color: "red"
    }

    signal released(rect rect)

    property bool square : false; // Zajistí, že obě strany obdelníku budou stejně velké

    function tick(delta){
            dummy.canSpawn = !visible
            if(!visible) return
            var mousePos = game.getMousePos()
            mousePos = Qt.vector2d(mousePos.x, mousePos.y)
            var posDelta = mousePos.minus(Qt.vector2d(myLayer.x + x, myLayer.y + y))
            if(posDelta.x > 0.0)
            {
                selectionRectangle.width = posDelta.x
            }
            else
            {
                selectionRectangle.width = Math.abs(posDelta.x)
                selectionRectangle.x = posDelta.x
            }
            if(posDelta.y > 0.0)
            {
                selectionRectangle.height = posDelta.y
            }
            else
            {
                selectionRectangle.height = Math.abs(posDelta.y)
                selectionRectangle.y = posDelta.y
            }

            if(square)
            {
                selectionRectangle.height = selectionRectangle.width
            }

            width = selectionRectangle.width
            height = selectionRectangle.height
            if(!game.isLeftMouseButtonPressed())
            {
                released(Qt.rect(x + selectionRectangle.x,
                                 y + selectionRectangle.y,
                                 selectionRectangle.width,
                                 selectionRectangle.height))
            }
    }
}
