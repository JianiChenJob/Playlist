/*! SideInfo.qml is the side info panel showing the album picture,
song name, artist and price of the selected song*/
import QtQuick 2.0

Item
{
    id: root
    width: 250
    height: album.height + name.height + artist.height + price.height

    property alias albumSrc: album.source
    property alias nameText: name.text
    property alias artistText: artist.text
    property alias priceText: price.text

    FontLoader
    {
        id: roboto
        source: "content/Roboto-Regular.ttf"
    }
    Image
    {
        id: album
        source: "content/controls/album.PNG"
        width: 210
        height: 210
        anchors.horizontalCenter: root.horizontalCenter
    }
    Text
    {
        id: name
        color: "#cac6c7"
        font.pixelSize: 20
        anchors.horizontalCenter: root.horizontalCenter
        anchors.top: album.bottom
        anchors.topMargin: 30
        font.family: roboto.name
        text: ""
    }
    Text
    {
        id: artist
        color: "#cac6c7"
        font.pixelSize: 20
        anchors.horizontalCenter: root.horizontalCenter
        anchors.top: name.bottom
        anchors.topMargin: 30
        font.family: roboto.name
        text: ""
    }
    Text
    {
        id: price
        color: "#cac6c7"
        font.pixelSize: 20
        anchors.horizontalCenter: root.horizontalCenter
        anchors.top: artist.bottom
        anchors.topMargin: 30
        font.family: roboto.name
        text: ""
    }

}
