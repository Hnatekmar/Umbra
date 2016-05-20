import QtQuick 2.0

Item {
    property string urlOn: ""
    property string urlOff: ""
    property bool selected: false
    signal clicked(bool selected)
    Image{
        id: imgOff
        source: urlOff
        visible: !selected
        anchors.centerIn: parent
    }
    Image{
        id: imgOn
        source: urlOn
        visible: selected
        anchors.centerIn: parent
    }
    width: imgOn.width > imgOff.width ? imgOn.width : imgOff.width
    height: imgOn.height > imgOff.height ? imgOn.height : imgOff.height
    MouseArea{
        width: parent.width
        height: parent.height
        onClicked: {
            selected = !selected
            parent.clicked(selected)
        }
    }
}
