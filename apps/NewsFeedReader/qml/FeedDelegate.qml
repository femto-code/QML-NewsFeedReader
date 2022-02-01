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
        //Text{ text: "  title"; font.pointSize: 12; color: "red" ; elide: Text.ElideRight; width: feedView.width}
        //Text{ text: modelData.title; font.pointSize: 15 ; elide: Text.ElideRight; width: feedView.width}
        Text{ text: modelData.title; font.pointSize: 15 ; width: feedView.width; wrapMode: Text.WordWrap; rightPadding: 10}
        //Text{ text: "  link"; font.pointSize: 12; color: "red" ; elide: Text.ElideRight; width: feedView.width}
        Text{
            text: "<a href=\""+modelData.link+"\">"+modelData.link+"</a>"
            font.pointSize: 9
//            elide: Text.ElideRight
            width: feedView.width
            onLinkActivated: Qt.openUrlExternally(link)
//            MouseArea {
//                id: mouseArea
//                anchors.fill: parent
//                cursorShape: Qt.PointingHandCursor
//            }
        }
        //Text{ text: "  pubDate"; font.pointSize: 12; color: "red" ; elide: Text.ElideRight; width: feedView.width}
        Text{ text: modelData.pubDate; font.pointSize: 10 ; elide: Text.ElideRight; width: feedView.width}
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
                width: parent.width
                height: parent.height
                text: modelData.description;
                wrapMode: Text.WordWrap
            }
        }

    }

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
