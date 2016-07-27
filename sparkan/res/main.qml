import QtQuick 2.5
import QtQuick.Window 2.2


Window {
    visible: true
    width: 1024
    height: 600
    title: qsTr("Hello World")

    Text {
        visible: false
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

    AuthenticationWindow {
        visible: true
        anchors.fill: parent
    }

}
