import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts


Rectangle{
    id: feedSources
    width: view.width
    height: 30
    border.width: 2; border.color: "lightsteelblue"

    Row {

        Rectangle {
            width: view.width - 20
            height: 30
            Row{
                spacing: 5
                Text{ text: "title"; font.pointSize: 12; color: "red" }
                Text{ text: modelData.title; font.pointSize: 10 }
            }
        }
        Rectangle {
            width: 20
            height: 30
            Image {
                id: deleteButton
                opacity: 0.7
                height: 20
                width: 20
                clip: true
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

    //        Image {
    //            id: image
    //            source: "delete-button-png-28557.png"
    //            smooth: true; opacity: 1.0
    //            height: 10
    //            width: 10
    //            clip: true


    //            Behavior on opacity { NumberAnimation { easing.type: Easing.OutQuad } }
    //        }

}
