import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

Rectangle{
    id: feedView
    width: viewRect.width
    height: 100
    border.width: 2; border.color: Universal.color(Universal.Lime)
    clip: true

    states: [
        State {
            name: "item"
            PropertyChanges { target: itemView; visible: true }
            PropertyChanges { target: descriptionView; visible: false }
        },
        State {
            name: "description"
            PropertyChanges { target: itemView; visible: false }
            PropertyChanges { target: descriptionView; visible: true }
        }
    ]

    Column{
        id: itemView
        visible: true
        leftPadding: 10
//        rightPadding: 10
        topPadding: 10
        Text{ text: modelData.title; font.pointSize: 15 ; width: feedView.width; wrapMode: Text.WordWrap; rightPadding: 10}
        Text{
            text: "<a href=\""+modelData.link+"\">"+modelData.link+"</a>"
            font.pointSize: 9
            width: feedView.width
            onLinkActivated: Qt.openUrlExternally(link)
//            MouseArea {
//                id: mouseArea
//                anchors.fill: parent
//                cursorShape: Qt.PointingHandCursor
//            }
        }
        Text{ text: modelData.pubDate; font.pointSize: 10 ; elide: Text.ElideRight; width: feedView.width}

        Button{
            id: btnDescription
            width: 50
            height: 20
            text: "Show more"
            MouseArea{
                anchors.fill: parent
                onPressed:{
                    feedView.height = 200
                    switch (feedView.state){
                    case "item":
                        feedView.state = "description"
                        break;
                    case "description":
                        feedView.state = "item"
                        break;
                    default:
                        feedView.state = "item"
                    }
                }
            }
        }
    }
    Column{
        id: descriptionView
        visible: false
        width: parent.width
        height: parent.height
        ScrollView {
            id: view
            width: parent.width
            height: parent.height
                TextArea {
                    id: descriptionText
                    width: parent.width
                    height: parent.height - 20
                    text: modelData.description;
                    wrapMode: Text.WordWrap
                }

                Button{
                    id: btnDescription2
                    width: 50
                    height: 20
                    text: "Show more"
                    anchors.top: descriptionText.bottom
                    MouseArea{
                        anchors.fill: parent
                        onPressed:{
                            switch (feedView.state){
                            case "item":
                                feedView.state = "description"
                                break;
                            case "description":
                                feedView.state = "item"
                                break;
                            default:
                                feedView.state = "item"
                            }
                        }
                    }
                }
        }
    }
}
