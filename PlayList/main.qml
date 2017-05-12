import QtQuick 2.6
import QtQuick.Window 2.2

import QtGraphicalEffects 1.0

Window {
    visible: true
    width: 1920
    height: 1080
    title: qsTr("Itunes Top 100")

    Item
    {
        id: root
        anchors.fill: parent
        focus: true

        Keys.onEscapePressed: Qt.quit()
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

        List
        {
            id: playlist
            onSongClicked:
            {
                audio_control.audioFilepath = preview;
                audio_control.audioTitle = songName + " - " + artist;
                audio_control.enabled = true;
                audio_control.videoPreviewImageFilepath = imageSource;
                console.log("bkg source = ", imageSource)
                bkg.source = imageSource;
                console.log("bkg source = ", bkg.source)
                bkg.visible = true;
            }
        }
        AudioControl
        {
            id: audio_control
            onPlaying: playlist.activatePlayingSong(audio_control.audioFilepath, true);
            onStopped: playlist.activatePlayingSong(audio_control.audioFilepath, false);
            onAudioFilepathChanged:
            {
                playlist.switchPlayingSong();
                playlist.activatePlayingSong(audio_control.audioFilepath, true);


            }

        }
    }
}
