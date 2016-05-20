import QtQuick 2.5
import QtQuick.Window 2.0
import Umbra 1.0

Window
{
    id: window
    width: 1024
    height: 800
    x:20
    y:20
    visible: true
    color: "gray"

    Component.onCompleted: {
        //window.visibility = Window.FullScreen
    }

    Game
    {
        id: game
        width: parent.width
        height: parent.height
        Sandbox{}
    }
}
