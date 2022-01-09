import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts


ColumnLayout{
    spacing: 10
    Layout.minimumWidth: 500
    Text{ text: "url"; font.pointSize: 12; color: "red" }
    Text{ text: modelData.url; font.pointSize: 20 }
    Text{ text: "title"; font.pointSize: 12; color: "red" }
    Text{ text: modelData.item.title; font.pointSize: 20 }
    Text{ text: "pubDate"; font.pointSize: 12; color: "red" }
    Text{ text: modelData.item.pubDate; font.pointSize: 20 }
}
