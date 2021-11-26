import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

//ApplicationWindow {
//    width: 1024
//    height: 768

//    property alias tst_mainStackView: mainStackView

//    StackView {
//        id: mainStackView
//        anchors.fill: parent

//        initialItem: Qt.resolvedUrl("ExampleStackPage.qml")
//    }

//    Component.onCompleted: show()
//}

ApplicationWindow {
    id: mainWindow
    title: qsTr("News Feed Reader")
    width: 640
    height: 480
    visible: true

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
            }

            Button {
                text: "Push"
                onClicked: stack.push("qrc:/feedView.qml")
                anchors.top: test.bottom
            }
        }
    }
}
