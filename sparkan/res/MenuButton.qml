import QtQuick 2.0

Rectangle{
    width: parent.width
    height: parent.width
    property url isource: ""
    signal click(real xPosition, real yPosition)
    Image {
        width: 48
        height: width
        anchors.centerIn: parent
        source: isource
        antialiasing: true

    }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            parent.color = "lightgrey"
        }
        onExited: {
            parent.color = "white"
        }
        onClicked: {
            click(mouse.x, mouse.y)
        }
    }
}
