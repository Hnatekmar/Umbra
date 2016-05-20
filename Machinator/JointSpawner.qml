import QtQuick 2.0
import Umbra 1.0

Entity {
    property PhysicEntity a: null
    property PhysicEntity b: null
    property bool disabled: false
    property var component: Qt.createComponent("WeldJointWrapper.qml")

    function clicked(entity)
    {
        if(disabled) return
        if(a != null)
        {
            b = entity
            if(component.status === Component.Ready)
            {
                join()
            }
            else
            {
                component.statusChanged.connect(join)
            }
            disabled = true
        }
        else
        {
            a = entity
        }
    }

    function join()
    {
        component.createObject(parent, {"bodyA" : a, "bodyB" : b})
    }

    Component.onCompleted: {
        dummy.entityClicked.connect(clicked)
    }
}
