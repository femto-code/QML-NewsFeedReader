import QtQuick
import QtQuick.Controls

Item {

    id: feed

    Rectangle{
        anchors.fill: parent
        Text {
            id: test
            text: qsTr("Add new Feed")
            anchors.centerIn: parent
        }

        Button {
            id: addButton
            text: "Add"
            onClicked: {test.text = "New Feed added"}
            anchors.top: test.bottom
        }

        Button {
            text: "Pop"
            onClicked: stack.pop()
            anchors.top: addButton.bottom
        }
    }
}
