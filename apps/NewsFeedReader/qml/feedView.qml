import QtQuick
import QtQuick.Controls

Item {
    id: feed

    Rectangle{
        anchors.fill: parent
        Text {
            id: test
            text: qsTr("Look at all my fancy Feeds")
            anchors.centerIn: parent
        }

        Button {
            id: pushButton
            text: "Push"
            onClicked: stack.push("qrc:/feedAdd.qml")
            anchors.top: test.bottom
        }


        Button {
            id: popButton
            text: "Pop"
            onClicked: stack.pop()
            anchors.top: pushButton.bottom
        }
    }
}
