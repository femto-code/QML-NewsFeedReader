import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts

Rectangle{
    id: feedView
    width: mainWindow.width
    height: 130
    border.width: 2; border.color: "lightsteelblue"
    Column{
        Text{ text: "title"; font.pointSize: 12; color: "red" }
        Text{ text: modelData.title; font.pointSize: 10 }
        Text{ text: "link"; font.pointSize: 12; color: "red" }
        Text{ text: modelData.link; font.pointSize: 10 }
        Text{ text: "pubDate"; font.pointSize: 12; color: "red" }
        Text{ text: modelData.pubDate; font.pointSize: 10 }
    }
    MouseArea {
        anchors.fill: parent
        onPressed: {parent.scale = 0.9}
        onReleased: {parent.scale = 1.0}
    }
}
