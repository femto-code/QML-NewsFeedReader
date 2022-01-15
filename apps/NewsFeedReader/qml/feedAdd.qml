import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


    Rectangle{
        width: mainWindow.width


        ColumnLayout {
            Layout.topMargin: 5
            width: parent.width

            Rectangle{
                id: title
                height: 25
                width: parent.width
                color: "lightsteelblue"
                Text {
                    text: "Manage your Feeds"
                    anchors.centerIn: parent
                    }
            }

            Rectangle {
                id: addRect
                width: parent.width

                height: 20

                Row {
                    TextField {
                        id: feedUrl
                        width: 200
                        placeholderText: "Please insert Feed Url..."

                    }

                    Button {
                        id: addButton
                        height: 20
                        width: 50
                        text: "Add"
                        onClicked: {
                            feedList.add(feedUrl.text);
                            feedList.debugFeedList();
                            feedUrl.text = "";
                        }
                    }
                }
            }
            Rectangle {
                id: urlListView
                width: parent.width
                //height: Layout.fillHeight
                height: 200

                ListView {
                    id: view
                    anchors {fill: parent; margins: 2}

                    delegate: FeedManageDelegate {}
                    model: feedList.feedItems
                    spacing: 4
                    cacheBuffer: 50
                    clip: true
                }

            }

            Rectangle {
                id: backButton
                height: 20
                Layout.alignment: Qt.AlignBottom

                Button {
                    height: parent.height
                    width: 50
                    text: "Back"
                    onClicked: stack.pop()
                }
            }
        }

        Connections {
            target: feedList
        }

    }


