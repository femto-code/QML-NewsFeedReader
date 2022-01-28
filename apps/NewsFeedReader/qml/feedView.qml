import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: feed

    Column{

        width: mainWindow.width
        height: mainWindow.height

        Rectangle {
            id:titleRect
            color: "lightsteelblue"
            width: parent.width
            height: parent.height / 10
            Text {
                id: test
                text: qsTr("Look at all my fancy Feeds")
                anchors.centerIn: parent
            }
        }

        Rectangle{
            id: viewRect
            border.color: "lightsteelblue"
            //anchors.top: titleRect.bottom
            width: parent.width
            height: parent.height / 1.5

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
