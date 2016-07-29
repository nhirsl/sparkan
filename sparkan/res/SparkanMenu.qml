import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.3

MenuBar
    {
        Menu {
            title: "Sparkan"

            MenuItem
            {
                visible: Me.displayName.length > 0
                text: Me.displayName
                onTriggered:
                {
                    userProfileId.visible = true;
                }

            }

            MenuItem
            {
                text: "About"
                onTriggered:
                {
                    aboutWindowId.visible = true;
                }
            }

            MenuItem
            {
                text: "Quit"
                onTriggered:
                {
                   Qt.quit();
                }
            }
        }

    }

