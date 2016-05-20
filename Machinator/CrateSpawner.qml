import QtQuick 2.0
import Umbra 1.0

SelectionRectangle {
    width: 50
    id: selector
    property var component : Qt.createComponent("Crate.qml")

    onReleased: {
        if(component.status === Component.Ready)
        {
            var cm = component.incubateObject(myLayer, {
                                    "x" : rect.x,
                                    "y" : rect.y,
                                    "width" : rect.width,
                                    "height" : rect.height,
                                    "bodyType" : gui.staticBody ? PhysicEntity.STATIC : PhysicEntity.DYNAMIC
                                   })
            if(cm.status != Component.Ready)
            {
                cm.onStatusChanged = function()
                {
                    selector.visible = false
                }
            }
            else
            {
                selector.visible = false
            }
        }
    }
}
