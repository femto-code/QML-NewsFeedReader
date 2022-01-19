import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts


Rectangle{
    id: feedSources
    width: view.width
    height: 25
    border.width: 2; border.color: "lightsteelblue"

    Row {
        spacing: 5
        Rectangle {
            width: view.width - 30
            height: 15
            Row{
                spacing: 5
                Text{ text: "name"; font.pointSize: 15; color: "red" ; font.bold: true}
                Text{ text: modelData.name; font.pointSize: 15 }
            }
        }
        Rectangle {
            width: 15
            height: 15
            Image {
                id: deleteButton
                opacity: 0.7
                anchors.fill: parent
                clip: true
                source: "delete-button-png-28557.png"
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons
                    onClicked: {
                        feedList.deleteSrc(modelData.name);
                    }
                    onEntered: {
                        deleteButton.opacity = 1.0
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
