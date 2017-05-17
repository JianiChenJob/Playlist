import QtQuick 2.6
import QtQuick.Window 2.2

import QtGraphicalEffects 1.0

Window {
    visible: true
    width: 1920
    height: 1080
    title: qsTr("Itunes Top 100")
    visibility: "FullScreen"

    Item
    {
        id: root
        anchors.fill: parent
        focus: true

        Keys.onEscapePressed: Qt.quit()

        /*! roboto font */
        FontLoader
        {
            id: roboto
            source: "content/Roboto-Regular.ttf"
        }
        /*! for each song, the bkg is its album image */
        Image
        {
            id: bkg
            anchors.fill: parent
            visible: false
        }
        FastBlur
        {
            anchors.fill: bkg
            source: bkg
            radius: 32
        }
        Rectangle
        {
            anchors.fill: parent
            color: "#404236"
            opacity: 0.9
        }
        /*! play list title */
        Text
        {
            id: title
            text: "ITUNES STORE: TOP 100 SONGS"
            color: "#ffffff"
            font.pixelSize: 25
            x: 15; y: 20
            font.family: roboto.name
        }
        /*! play list */
        List
        {
            id: playlist
            x: 182; y: 120
            onSongClicked:
            {
                //when select a song, set song information to controls and side info panel.
                audio_control.audioFilepath = preview;
                audio_control.audioTitle = songName + " - " + artist;
                audio_control.enabled = true;
                audio_control.videoPreviewImageFilepath = imageSource;

                bkg.source = imageSource;
                bkg.visible = true;

                side_info.albumSrc = imageSource;
                side_info.nameText = "Name : " + songName;
                side_info.artistText = "Artist : " + artist;
                side_info.priceText = "Price : " + price;
            }
        }
        /*! audio control to play and pause a song */
        AudioControl
        {
            id: audio_control
            onPlaying: playlist.activatePlayingSong(audio_control.audioFilepath, true);
            onStopped: playlist.activatePlayingSong(audio_control.audioFilepath, false);
            onAudioFilepathChanged:
            {
                //set all songs to stop
                playlist.switchPlayingSong();
                //set the playing song row to play animation
                playlist.activatePlayingSong(audio_control.audioFilepath, true);
            }

        }
        /*! side info panel shows the album picture, song name, artist and price */
        SideInfo
        {
            id: side_info
            x: 1522
            y: 120
        }
    }
}
