import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

Rectangle{
    id: feedView
    width: viewRect.width
    border.width: 2; border.color: Universal.color(Universal.Lime)
    clip: true
    height: itit.paintedHeight + 30 + 50

    states: [
        State {
            name: "on"
            PropertyChanges { target: feedView; height: itit.paintedHeight + 180 }
            PropertyChanges { target: descexpand; visible: true }
        },
        State {
            name: "off"
            PropertyChanges { target: feedView; height: itit.paintedHeight + 30 + 50 }
            PropertyChanges { target: descexpand; visible: false }
        }
    ]

    Column{
        id: itemView
        visible: true
        leftPadding: 10
//        rightPadding: 10
        topPadding: 10
        width: parent.width
        height: parent.height
        spacing: 3
        Text{ id: itit; text: modelData.title; font.pointSize: 15 ; width: feedView.width; wrapMode: Text.WordWrap; rightPadding: 10}
        Text{
            text: "<a href=\""+modelData.link+"\">"+modelData.link+"</a>"
            font.pointSize: 9
            width: feedView.width
            onLinkActivated: Qt.openUrlExternally(link)
            // QT6?? TODO!
//            MouseArea {
//                id: mouseArea
//                anchors.fill: parent
//                cursorShape: Qt.PointingHandCursor
//            }
        }
        Text{ text: modelData.pubDate; font.pointSize: 10 ; elide: Text.ElideRight; width: feedView.width}


        Button{
            id: btnDescription
            width: 150
            height: 20
            text: "Show / Hide"
            MouseArea{
                anchors.fill: parent
                onPressed:{

                    switch (feedView.state){
                    case "on":
                        feedView.state = "off"
                        break;
                    case "off":
                        feedView.state = "on"
                        break;
                    default:
                        feedView.state = "on"
                    }
                }
            }
        }

        ScrollView {

            id: descexpand
            visible: false
            width: parent.width - 20
            height: 100
                TextArea {
                    id: descriptionText
                    width: parent.width
                    height: parent.height - 20
                    text: modelData.description;
                    wrapMode: Text.WordWrap
                }

        }

    }

}
