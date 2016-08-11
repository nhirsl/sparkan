import QtQuick 2.5
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0


Rectangle{
    width: parent.width
    height: parent.width
    property url isource: ""
    signal click()

    Image {
        id: image
        anchors.fill: parent
        source: isource
        //fillMode: Image.PreserveAspectCrop
        visible: false // Do not forget to make original pic insisible
    }
    Rectangle {
        id: mask
        anchors { fill: parent; margins: 18}
        color: "black";
        radius: width / 2
        clip: true
        visible: false

    }
    OpacityMask {
        anchors.fill: mask
        source: image
        maskSource: mask
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
            click()
        }
    }
}
