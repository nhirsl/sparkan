import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.3

ApplicationWindow
{
    id: aplicationWindowId
    visible: true
    width: 1024
    height: 600
    title: qsTr("Hello World")
    x: (Screen.width - aplicationWindowId.width) / 2
    y: (Screen.height - aplicationWindowId.height) / 2

    menuBar: SparkanMenu
    {
        id: sparkanMenuId
    }

    Window
    {
        id: aboutWindowId
        width: 400
        height:250
        visible:false
        x: aplicationWindowId.x
        y: aplicationWindowId.y
    }

    Window
    {
        id: userProfileId
        height: 400
        width: 400
        visible:false
        title: Me.displayName
        x: aplicationWindowId.x
        y: aplicationWindowId.y
        Image
        {
            anchors.fill: parent
            source: Me.avatar
        }
    }

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
        id: authenticationWindowId
        visible: myBrowser.visible
        focus: myBrowser.visible
        anchors.fill: parent
    }


}
