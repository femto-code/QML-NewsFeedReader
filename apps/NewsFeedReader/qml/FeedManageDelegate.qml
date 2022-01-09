import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts


Rectangle{
    id: feedSources
    width: view.width
    height: 30
    border.width: 2; border.color: "lightsteelblue"

    RowLayout {
        Text {
            id: feedName
            text: "John Doe's RSS Feed"
        }

        Image {
            id: image
            source: "delete-button-png-28557.png"
            smooth: true; opacity: 1.0
            height: 10
            width: 10
            clip: true


            Behavior on opacity { NumberAnimation { easing.type: Easing.OutQuad } }
        }
        Image {
            id: deleteButton
            opacity: 0.7
            source: "delete-button-png-28557.png"
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.AllButtons
                onClicked: {
                    console.log("delete..");
                }
                onEntered: {
                    addButton.opacity = 1.0
                }

            }
        }
    }
}
