import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

Item {
    id: feed
    width: mainWindow.width

    ColumnLayout{
        Layout.topMargin: 5
        width: parent.width
        spacing: 10

        Rectangle{
            id: titleRect
            color: Universal.color(Universal.Lime)
            Layout.preferredWidth: mainWindow.width
            Layout.preferredHeight: mainWindow.height / 6
            Text {
                text: qsTr("Look at all my fancy Feeds")
                anchors.centerIn: parent
                font.pixelSize: 20
            }
        }

        Rectangle{
            id: viewRect
            border.color: Universal.color(Universal.Lime)
            //anchors.top: titleRect.bottom
            Layout.preferredWidth: mainWindow.width - 16
            Layout.preferredHeight: mainWindow.height * 4 / 6
            Layout.leftMargin: 8
            Layout.rightMargin: 8

            ListView{
                id: view
                width: parent.width
                height: parent.height
                clip: true
                delegate: FeedDelegate {}
                spacing: 4
        //        cacheBuffer: 20
                model: feedList.feedItems
            }
        }

        Rectangle{

            Layout.preferredWidth: mainWindow.width - 16
            Layout.preferredHeight: mainWindow.height * 1 / 6 - 30

            border.width: 2; border.color: Universal.color(Universal.Lime)

            Layout.leftMargin: 8
            Layout.rightMargin: 8
            //Layout.topMargin: 8

            RowLayout {
                id: rowLayout
                anchors.fill: parent


                Button {
                    id: pushButton
                    text: "Push"
                    onClicked: stack.push("qrc:/feedAdd.qml")
                }

                Button {
                    id: popButton
                    text: "Pop"
                    onClicked: stack.pop()
                }
                Button {
                    id: debugBtn
                    text: "Debug"
                    onClicked: feedList.debugFeedList()
                }
                Button {
                    id: saveBtn
                    text: "Save"
                    onClicked: feedList.saveToDB()
                }

            }


        }
    }

}
