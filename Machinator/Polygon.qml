import QtQuick 2.0
import Umbra 1.0

PhysicEntity
{
    bodyType: PhysicEntity.DYNAMIC
    property double size: 500.0
    fixture: PolygonFixture
    {
        id: fixture
        points:[
            Qt.point(0.0, 0.0),
            Qt.point(0.0, 50.0),
            Qt.point(50.0, 0.0)
        ]
    }

    Canvas{
        id: canvas
        width: 50
        height: 50
        antialiasing: true
        property bool enabled: mouseArea.enabled
        onPaint: {
            var ctx = getContext("2d");
            ctx.strokeStyle = enabled ? "orange" : "white";
            ctx.lineWidth = 2;
            ctx.moveTo(0, 0);
            ctx.lineTo(50, 0);
            ctx.lineTo(0,50);
            ctx.lineTo(0, 0);
            ctx.stroke();
        }
    }

    function tick(delta) {
        if (mouseArea.drag.active) {
            setAngularVelocity(0)
            setLinearVelocity(Qt.vector2d(0, 0))
        }
        if (game.isPressed(Qt.Key_Delete) && mouseArea.enabled) {
            destroy()
        }
    }

    MouseArea{
        id:mouseArea
        width: 50
        height: 50
        hoverEnabled: true
        acceptedButtons: Qt.RightButton
        drag.target: parent
        property bool enabled: false
        onEntered: {
            enabled = true
            canvas.requestPaint()
        }
        onExited: {
            enabled = false
            canvas.requestPaint()
        }
        onClicked: {
            dummy.onClicked(parent)
        }
        onWheel: {
            parent.rotation += wheel.angleDelta.y / 120
            parent.rotation = parent.rotation % 360
        }
    }
}
