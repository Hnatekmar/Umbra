import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0


Rectangle{

    Component.onCompleted: {
        items.currentItem.scale = 1.5
    }

    color:"#b7b3b3"
    width: game.width
    height: 100
    property string selected: "BallSpawner"
    property bool staticBody: false
    ListView {
        id: items
        x: 120
        width: parent.width
        height: parent.height
        orientation: ListView.Horizontal
        model: ListModel {
            ListElement {
                name: "Kruh"
                resourceName: "BallSpawner"
                iconName: "circle.png"
            }
            ListElement{
                name: "Polygon"
                resourceName: "Polygon"
                iconName:"triangle.png"
            }
            ListElement {
                name: "Obdelnik"
                resourceName: "CrateSpawner"
                iconName:"rectangle.png"
            }
            ListElement {
                name: "Částice"
                resourceName: "ParticleSpawner"
                iconName: "particles.png"
            }
            ListElement {
                name: "Joint"
                resourceName: "JointSpawner"
                iconName: "wheel.png"
            }
            ListElement{
                name: "ElasticParticle"
                resourceName: "ElasticParticleSpawner"
                iconName: "elastic.png"
            }
        }
        delegate: Component {
            Item {
                width: image.width * 2
                height: image.height
                Image {
                    anchors.centerIn: parent
                    id: image
                    width: 64
                    height: 64
                    source: "Game/Menu/" + iconName
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        items.currentItem.scale = 1.0
                        items.currentIndex = index
                        items.currentItem.scale = 1.5
                        gui.selected = resourceName
                    }
                }
            }
        }
    }

    ColumnLayout{
        ImageButton{
            id: playButton
            selected: true
            urlOn: "Game/Tools/play_on.png"
            urlOff: "Game/Tools/play_off.png"
            onClicked: {
                pauseButton.selected = false
                myLayer.unPause()
            }
        }
        ImageButton{
            id: pauseButton
            urlOn: "Game/Tools/pause_on.png"
            urlOff: "Game/Tools/pause_off.png"
            onClicked: {
                playButton.selected = false
                myLayer.pause()
            }
        }
    }
    Slider{
        x:50
        height: 80
        maximumValue: 1.0
        minimumValue: 0.0
        orientation: Qt.Vertical
        onValueChanged: {
            myLayer.gravitationY = -value * 9.8
        }
        style: SliderStyle{
            handle: Rectangle{
                color: "black"
                width: 5
                height: 20
            }
            groove: Rectangle{
                color: "black"
                implicitWidth: 200
                implicitHeight: 8
            }
        }
    }
    Row{
        x: 70
        Image {
            source: "Game/Tools/dynamic.png"
        }
        ImageButton{
            y: 25
            selected: true
            urlOn: "Game/Tools/switch_on.png"
            urlOff: "Game/Tools/switch_off.png"
            onClicked: {
                gui.staticBody = !selected
            }
        }
    }
}
