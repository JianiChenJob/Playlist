/*! SongEntry.qml shows song name, artist and duration and
allows user to select a song to play*/
import QtQuick 2.0

Item
{
    id: root

    height: 63
    width: 1196

    property int rowSpacing: 0

    property string songName: ""

    property string artist: ""

    property var duration

    property string price: ""

    property string preview: ""

    property string imageSource: ""

    property int songID: 0

    signal songClicked(var preview, var imageSource, var songName, var artist, var duration, var price);

    FontLoader
    {
        id: roboto
        source: "content/Roboto-Regular.ttf"
    }

    Rectangle
    {
        color: "#cac6c7"
        opacity: 0.1
        width: root.width
        height: 1
        radius: 1

    }

    Text
    {
        id: song_id
        text: songID
        color: "#cac6c7"
        font.pixelSize: 20
        anchors.verticalCenter: root.verticalCenter
        font.family: roboto.name
        Behavior on opacity
        {
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }

    }
    PlayBarsAnimation
    {
        id: three_bars_animation
        anchors.verticalCenter: root.verticalCenter
        opacity: 0.0
        Behavior on opacity
        {
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }
    }

    Text
    {
        id: song_name
        text: songName
        color: "#cac6c7"
        font.pixelSize: 20
        x: 40
        anchors.verticalCenter: root.verticalCenter
        font.family: roboto.name
    }
    Text
    {
        id: song_artist
        text: artist
        color: "#cac6c7"
        font.pixelSize: 20
        x: 730
        anchors.verticalCenter: root.verticalCenter
        font.family: roboto.name
    }
    Text
    {
        id: song_duration
        text: duration
        color: "#cac6c7"
        font.pixelSize: 20
        x: 730 + 370
        anchors.verticalCenter: root.verticalCenter
        font.family: roboto.name
    }
    MultiPointTouchArea
    {
        id: tap_area
        anchors.fill: parent
        onPressed:
        {
            root.songClicked(preview, imageSource, songName, artist, duration, price);
        }
    }

    function playing(active)
    {
        if(active)
        {
            song_artist.color = "#ffffff";
            song_name.color = "#ffffff";
            three_bars_animation.opacity = 1.0;
            song_id.opacity = 0.0;
        }
        else
        {
            song_artist.color = "#cac6c7";
            song_name.color = "#cac6c7";
            three_bars_animation.opacity = 0.0;
            song_id.opacity = 1.0;
        }


    }


}
