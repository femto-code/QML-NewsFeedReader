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
    title: qsTr("Hello World")
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

        Row {
            spacing: 10

            Button {
                text: "Push"
                onClicked: stack.push(mainView)
            }
            Button {
                text: "Pop"
                enabled: stack.depth > 1
                onClicked: stack.pop()

            }
            Text {
                text: stack.depth
            }
        }
    }
}
