import QtQuick 2.5
import Umbra 1.0

Scene
{
    MouseArea
    {
        drag.target: myLayer
        width: window.width
        height: window.height
        acceptedButtons: Qt.RightButton
    }
    Layer
    {
        id: myLayer
    }
    Gui
    {
        id: gui
        z: 99999
        y: game.height - gui.height
    }
    Layer
    {
        PositionLocator{
            y:0
        }

        DummySpawner
        {
            id: dummy
            target: myLayer
        }
    }
}
