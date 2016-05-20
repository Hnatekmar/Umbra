import QtQuick 2.0
import Umbra 1.0

SelectionRectangle {
    width: 50
    square: true
    property var component: Qt.createComponent("Ball.qml")
    onReleased: {
        if(component.status === Component.Ready)
        {
            var cm = component.incubateObject(parent, {
                                    "x" : rect.x,
                                    "y" : rect.y,
                                    "radius" : rect.width / 2,
                                    "bodyType" : gui.staticBody ? PhysicEntity.STATIC : PhysicEntity.DYNAMIC
                                   })
            visible = false
        }
    }
}
