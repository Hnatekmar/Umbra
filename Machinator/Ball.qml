import QtQuick 2.0
import Umbra 1.0

PhysicEntity {
    id: entity
    property real friction: 1.0
    property real density: 1.0
    property real restitution: 1.0
    property real radius: 25
    bodyType: PhysicEntity.DYNAMIC

    fixture: CircleFixture
        {
            id: circleFixture
            radius: entity.radius
            friction: entity.friction
            density: entity.density
            restitution: entity.restitution
        }
    Rectangle
    {
        id: circle
        width: entity.radius * 2
        height: entity.radius * 2
        radius: entity.radius
        color: "transparent"
        border.color: "white"
        border.width: 2
    }

    function tick(delta)
    {
        if(mouseArea.drag.active)
        {
            setAngularVelocity(0)
            setLinearVelocity(Qt.vector2d(0, 0))
        }
        if(game.isPressed(Qt.Key_Delete) && mouseArea.hovering)
        {
            destroy()
        }
    }

    MouseArea
    {
        id: mouseArea
        drag.target: parent
        drag.threshold: 0
        width: entity.radius * 2
        height: entity.radius * 2
        hoverEnabled: true
        property bool hovering : false
        acceptedButtons: Qt.RightButton
        onEntered: {
            circle.border.color = "orange"
            hovering = true
        }
        onClicked: {
            dummy.onClicked(entity)
        }
        onExited: {
            circle.border.color = "white"
            hovering = false
        }
        onWheel: {
            var newSize = wheel.angleDelta.y / 120
            entity.radius += newSize
        }
    }
}
