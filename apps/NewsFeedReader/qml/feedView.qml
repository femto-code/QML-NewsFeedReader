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
            Layout.preferredHeight: mainWindow.height / 10
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
            Layout.preferredWidth: mainWindow.width
            Layout.preferredHeight: mainWindow.height * 2 / 3

            anchors {
                leftMargin: 20
                rightMargin: 20
            }

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
            anchors.top: viewRect.bottom

            Button {
                id: pushButton
                text: "Push"
                onClicked: stack.push("qrc:/feedAdd.qml")
                //anchors.top: test.bottom
            }

            Button {
                id: popButton
                text: "Pop"
                onClicked: stack.pop()
                anchors.top: pushButton.bottom
            }
            Button {
                id: debugBtn
                text: "Debug"
                onClicked: feedList.debugFeedList();
                anchors.top: popButton.bottom
            }
            Button {
                id: saveBtn
                text: "Save"
                onClicked: feedList.saveToDB();
                anchors.top: debugBtn.bottom
            }
        }
    }

}
