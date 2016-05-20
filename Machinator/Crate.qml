import QtQuick 2.0
import QtQml.Models 2.2
import Umbra 1.0

PhysicEntity // Entita, jejiž pozice a rotace se bude automaticky orientovat dle fyzikální simulace
{
    id: entity

    bodyType: PhysicEntity.DYNAMIC // Nestatické fyzikální těleso
    fixture: RectangleFixture // Definuje tvar fyzikálního tělesa
    {
        id: rectangleFixture
        width: entity.width
        height: entity.height
        friction: 10.0
        density: 1.0
        restitution: 1.0
    }

    Rectangle {
        // Definuje, jak entita vypadá čisté qml
        id: rectangle
        antialiasing: true
        color: "transparent"
        border.color: "white"
        width: entity.width
        height: entity.height
        border.width: 2
    }

    function tick(delta) {
        if (mouseArea.drag.active) {
            setAngularVelocity(0)
            setLinearVelocity(Qt.vector2d(0, 0))
        }
        if (game.isPressed(Qt.Key_Delete) && mouseArea.hovering) {
            destroy()
        }
    }

    MouseArea {
        id: mouseArea
        drag.target: parent
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.RightButton
        z: 500
        property bool hovering : false

        onEntered: {
            rectangle.border.color = "orange"
            hovering = true
        }
        onExited: {
            rectangle.border.color = "white"
            hovering = false
        }

        onClicked: {
            dummy.onClicked(entity)
        }

        onWheel: {
            if (drag.active) {
                var newSize = wheel.angleDelta.y / 120
                rectangle.width += newSize
                rectangle.height += newSize
                rectangleFixture.width = rectangle.width
                rectangleFixture.height = rectangle.height
            } else {
                parent.rotation += wheel.angleDelta.y / 120
                parent.rotation = parent.rotation % 360
            }
        }
    }
}
