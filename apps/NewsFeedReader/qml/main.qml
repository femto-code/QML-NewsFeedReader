import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

ApplicationWindow {
    id: mainWindow
    title: qsTr("News Feed Reader")
    width: 500
    height: 600
    visible: true
    minimumWidth: 400
    minimumHeight: 500


    Universal.theme: Universal.Light
    Universal.accent: Universal.Lime

    StackView {
        id: stack
        initialItem: mainView
        anchors.fill: parent
    }

    Component {
        id: mainView

        Rectangle{

            anchors.fill: mainWindow
            Text {
                id: test
                text: qsTr("Welcome to our NewsFeedReader")
                anchors.centerIn: parent
                font.pixelSize: 20
            }

            Rectangle {
                id: gobtn
                width: parent.width
                height: parent.height * 1/3
                anchors.top: test.bottom

                Button {
                    onClicked: stack.push("qrc:/feedView.qml")

                    anchors.centerIn: parent
                    height: 30
                    width: 100
                    text: "Get started"
                }

            }

        }
    }
}
