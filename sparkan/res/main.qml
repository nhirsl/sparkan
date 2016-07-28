import QtQuick 2.5
import QtQuick.Window 2.2


Window {
    visible: true
    width: 1024
    height: 600
    title: qsTr("Hello World")

    Column {
        visible: !myBrowser.visible
        anchors.centerIn: parent

        Image {
            width: 128
            height: 128
            id: avatarMeId
            source: Me.avatar
        }
        Text{
            text: Me.displayName
        }
    }

    AuthenticationWindow {
        visible: myBrowser.visible
        anchors.fill: parent
    }

}
