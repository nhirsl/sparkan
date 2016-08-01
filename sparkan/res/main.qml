import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.3

ApplicationWindow
{
    id: aplicationWindowId
    visible: true
    width: 1024
    height: 600
    title: qsTr("Hello Sparkan")
    x: (Screen.width - aplicationWindowId.width) / 2
    y: (Screen.height - aplicationWindowId.height) / 2

    menuBar: SparkanMenu{}

    Window
    {
        id: aboutWindowId
        width: 400
        height:250
        visible:false
        x: aplicationWindowId.x
        y: aplicationWindowId.y
        title: "Sparkan"

        Column{
            Text{
                text: "Sparkan 1.0 \nhttps://github.com/nhirsl/sparkan"
            }
            Text {
                text: "Developers"
            }
            Text {
                text: "Veljko Jasikovac \tveljko.jasikovac@gmail.com \tveljko.jasikovac \nNebojsa Karan \tnebojsakaran1011@gmail.com \tnebojsa1011 \nNenad Žikić \tnenad.zikic@gmail.com"
            }
            Text {
                text: "Development Lead"
            }
            Text {
                text: "Nemanja Hiršl nemhirsl@gmail.com http://alas.matf.bg.ac.rs/~mr97352/ nhirsl "
            }
        }
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
