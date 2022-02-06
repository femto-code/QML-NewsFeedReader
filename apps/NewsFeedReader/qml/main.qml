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

    property bool indiState : false

    StackView {
        id: stack
        initialItem: mainView
        anchors.fill: parent
    }

    Component {
        id: mainView

        Rectangle{
            id: mainRect
            Text {
                id: test
                text: qsTr("Welcome to our NewsFeedReader")
                anchors.centerIn: parent
                font.pixelSize: 20
            }

            Rectangle {
                id: gobtn
                width: parent.width
                height: parent.height * 1/4
                anchors.top: test.bottom

                Button {
                    onClicked: stack.push("qrc:/feedView.qml")
                    anchors.centerIn: parent
                    height: 30
                    width: 100
                    text: "Get started"
                }

            }
            Rectangle {
                id: busyRect
                width: parent.width
                height: 30
                anchors.top: gobtn.bottom

                BusyIndicator {
                    id: bIndi
                    anchors.centerIn: parent
                    anchors.top: mainRect.buttom
                    running: indiState
                }
            }
        }
    }

    Connections{
        target: feedList
        function onFeedAdded(){
            indiState = true
            console.log("Visible true")
        }

        function onAddFinished(){
            indiState = false
            console.log("Visible false")
        }
    }
}
