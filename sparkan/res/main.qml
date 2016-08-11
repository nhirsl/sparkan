import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3

ApplicationWindow
{
    id: aplicationWindowId
    visible: true
    width: 1024
    height: 600
    title: qsTr("Hello Sparkan")
    x: (Screen.width - aplicationWindowId.width) / 2
    y: (Screen.height - aplicationWindowId.height) / 2
    property real iconsize: 72

    Item {
        id: menuId
        width: iconsize
        height: parent.height
        visible: !myBrowser.visible

        Column {

            anchors.fill: parent
            MenuButton {
                width: iconsize
                height: iconsize

                isource: "images/Search.png"
            }


            MenuButton {
                width: iconsize
                height: iconsize

                isource: "images/Recents.png"
            }

            MenuButton {
                width: iconsize
                height: iconsize

                isource: "images/Teams.png"
            }

            MenuButton {
                width: iconsize
                height: iconsize

                isource: "images/Mentions.png"
            }
            MenuButton {
                width: iconsize
                height: iconsize
                isource: "images/Calls.png"
            }
            AvatarButton {
                width: iconsize
                height: iconsize

                isource: Me.avatar
                onClick: {
                    userProfileId.show()
                }
            }

            MenuButton {
                width: iconsize
                height: iconsize

                isource: "images/Settings.png"
                onClick: {
                    settingsMenuId.popup()
                }

                Menu {
                    id: settingsMenuId
                    style: MenuStyle {
                        frame: Component {
                            Rectangle {
                                anchors.fill: parent
                                color: "white"
                            }
                        }
                    }

                    MenuItem {
                        text: "Settings"

                    }
                    MenuItem {
                        text: "About"
                        onTriggered: {
                            aboutWindowId.show()
                        }
                    }
                    MenuItem {
                        text: "Send feedback"
                    }
                    MenuItem {
                        text: "Sparkan Help"
                    }
                    MenuItem {
                        text: "Sign Out"
                    }
                    MenuItem {
                        text: "Exit"
                        onTriggered: {
                            Qt.quit()
                        }
                    }
                }
            }
        }
    }

    Rectangle {

        anchors.left: menuId.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: "lightblue"
        border.color: "blue"
        border.width: 2
        visible: !myBrowser.visible
    }
    Window
    {
        id: aboutWindowId
        width: 400
        height:250
        visible:false
        x: aplicationWindowId.x
        y: aplicationWindowId.y
        title: "Sparkan"

        ListModel {
            id: developersListId
            ListElement { name:"Veljko Jasikovac"; email:"veljko.jasikovac@gmail.com"; role:"Developer"; }
            ListElement { name:"Nebojsa Karan"; email:"nebojsakaran1011@gmail.com"; role: "Developer"; }
            ListElement { name:"Nenad Žikić"; email:"nenad.zikic@gmail.com"; role:"Developer"; }
            ListElement { name:"Nemanja Hiršl"; email:"nemhirsl@gmail.com"; role:"Development Lead"; }
        }

        ListView {
            id: listViewId
            model: developersListId
            width: 400; height: 100;
            delegate: Row {
                Text {width:150; text: name; }
                Text {width:250; text:email; }
                Text {text:role}

            }
            section {
                property: "role"
                criteria: ViewSection.FullString
                labelPositioning: ViewSection.InlineLabels
                delegate: Rectangle {
                    width: listViewId.width
                    height: 30
                    color: "lightgrey"
                    Text {
                        text: section; font.pixelSize:  22
                    }

                }


            }
        }

        Column{
            visible: false
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


    AuthenticationWindow {
        id: authenticationWindowId
        visible: myBrowser.visible
        focus: myBrowser.visible
        anchors.fill: parent
    }


}

