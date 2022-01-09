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

                Rectangle {
                    id: titleRect
                    height: 25
                    anchors.centerIn: parent
                    Text {
                        text: "Manage your Feeds" }
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

//                    Image {
//                        id: addButton
//                        source: "add_button.png"
//                        width: 20
//                        height: 20
//                        MouseArea {
//                            Layout.fillHeight: parent.height
//                            Layout.fillWidth: parent.width
//                            acceptedButtons: Qt.AllButtons
//                            onClicked: {
//                                //feedList.add(feedUrl.text)
//                                console.log("clicked..");
//                            }
//                            onEntered: {
//                                addButton.opacity = 1
//                            }
//                        }
//                    }
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

                    spacing: 4
                    cacheBuffer: 50
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


