import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    id: feedView
    width: mainWindow.width
    height: 130
    border.width: 2; border.color: "lightsteelblue"
    clip: true

    states: [
        State {
            name: "item"
            PropertyChanges { target: itemView; opacity: 1 }
            PropertyChanges { target: descriptionView; opacity: 0 }
        },
        State {
            name: "description"
            PropertyChanges { target: itemView; opacity: 0 }
            PropertyChanges { target: descriptionView; opacity: 1 }
        }
    ]

    Column{
        id: itemView
        Text{ text: "  title"; font.pointSize: 12; color: "red" ; elide: Text.ElideRight; width: feedView.width}
        Text{ text: "  " + modelData.title; font.pointSize: 10 ; elide: Text.ElideRight; width: feedView.width}
        Text{ text: "  link"; font.pointSize: 12; color: "red" ; elide: Text.ElideRight; width: feedView.width}
        Text{ text: "  " + modelData.link; font.pointSize: 10 ; elide: Text.ElideRight; width: feedView.width}
        Text{ text: "  pubDate"; font.pointSize: 12; color: "red" ; elide: Text.ElideRight; width: feedView.width}
        Text{ text: "  " + modelData.pubDate; font.pointSize: 10 ; elide: Text.ElideRight; width: feedView.width}
    }
    Column{
        id: descriptionView
        opacity: 0
        Text{ text: modelData.description; elide: Text.ElideRight; width: feedView.width; wrapMode: Text.WordWrap}

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
