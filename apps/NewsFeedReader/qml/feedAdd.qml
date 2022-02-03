import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

Rectangle{
    width: mainWindow.width

    ColumnLayout {
        Layout.topMargin: 5
        width: parent.width
        spacing: 10

        Rectangle{
            id: title
            color: Universal.color(Universal.Lime)
            Layout.preferredWidth: mainWindow.width
            Layout.preferredHeight: mainWindow.height / 6
            Text {
                text: "Manage your Feeds"
                anchors.centerIn: parent
                font.pixelSize: 20
            }
        }

        Rectangle {
            id: addRect
            Layout.preferredWidth: mainWindow.width
            Layout.preferredHeight: mainWindow.height * 1 / 8

            RowLayout {
                spacing: 20
                anchors {
                    top: parent.top;
                    left: parent.left
                    right: parent.right
                    leftMargin: 20
                    rightMargin: 20
                    topMargin: mainWindow.height * 1/30
                }

                TextField {
                    id: feedUrl
                    Layout.fillWidth: true
                    width: parent.width * 2/3
                    placeholderText: "Please insert Feed Url..."

                }

                Button {
                    id: addButton
                    height: 20
                    width: 50
                    text: "Add"
                    onClicked: {
                        feedList.add(feedUrl.text);
                        //feedList.debugFeedList();
                        feedUrl.text = "";
                    }
                }
            }
        }
        Rectangle {
            id: urlListView
            Layout.preferredWidth: mainWindow.width
            Layout.preferredHeight: mainWindow.height * 1 / 4
            ListView {
                id: view
                anchors {fill: parent; margins: 2; leftMargin: 20; rightMargin: 20}

                delegate: FeedManageDelegate {}
                model: feedList.feedSources
                spacing: 4
                cacheBuffer: 50
                clip: true
            }

        }

        Rectangle {
            id: backButton
            Layout.preferredWidth: mainWindow.width
            Layout.preferredHeight: mainWindow.height * 1 / 6

            Button {
                anchors.centerIn: parent
                height: 30
                width: 50
                text: "Back"
                onClicked: stack.pop()
            }
        }
    }

    Connections {
        target: feedList
        function onFeedSourcesChanged()  {
//            stack.pop(null)
        }
    }
}


