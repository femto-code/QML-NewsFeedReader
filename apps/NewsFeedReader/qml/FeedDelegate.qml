import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts


ColumnLayout{
    Text{ text: "title"; font.pointSize: 12; color: "red" }
    Text{ text: modelData.title; font.pointSize: 20 }
    Text{ text: "link"; font.pointSize: 12; color: "red" }
    Text{ text: modelData.link; font.pointSize: 20 }
    Text{ text: "pubDate"; font.pointSize: 12; color: "red" }
    Text{ text: modelData.pubDate; font.pointSize: 20 }
}
