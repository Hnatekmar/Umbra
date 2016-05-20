import QtQuick 2.0
import Umbra 1.0

// Entita, která ukazuje pozici myši
Entity {
    y:50
    Text {
        id: positionText
        text: qsTr("0x0")
        color: "white"
    }
    function tick(delta)
    {
        var mousePos = game.getMousePos()
        positionText.text = qsTr((myLayer.x + mousePos.x) + "x" + (myLayer.y + mousePos.y))
    }
}
