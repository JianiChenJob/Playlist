/*! AudioControl.qml can be used to control a audio like playing or stopping*/

import QtQuick 2.7
import QtGraphicalEffects 1.0


import QtMultimedia 5.8
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item
{
    //=========================================================================
    // ROOT ITEM PROPERTIES
    //=========================================================================
    property alias audioFilepath: player.source

    property string videoPreviewImageFilepath: ""

    property string audioTitle: ""

    property bool autoPlay: true

    signal playing();

    signal stopped();
    //=========================================================================
    // ROOT ITEM SETTINGS
    //=========================================================================
    id: root

    opacity: 1.0

    enabled: false

    //=========================================================================
    // UI
    //=========================================================================
    FontLoader
    {
        id: roboto
        source: "content/Roboto-Regular.ttf"
    }

    Audio
    {
        id: player
        onStatusChanged:
        {
            if(status === MediaPlayer.EndOfMedia)
            {
                stopButton.visible = false;

                playButton.visible = true;

            }
            else if(status === MediaPlayer.Loaded)
            {
                bar_width_behavior.duration = 1000;
                grid_x_behavior.duration = 1000;
            }

        }
        onPlaying: root.playing();
        onPaused: root.stopped();
        onStopped: root.stopped();
    }

    Item
    {
        id: controls_dock
        y: 0
        enabled: opacity === 1.0
        Image
        {
            id: buttonsBackground

            x: 0; y: 970
            width: 1920

            source: "content/controls/dock.png"

            Image
            {
                id: barBackground

                x: 443
                y: 63

                source: "content/controls/Progress bar BG.png"

                width: 1250

                Item
                {
                    clip: true
                    width:  player.duration > 0 ? getPlayerPosition(): 0
                    height: barBackground.height
                    Behavior on width
                    {
                        NumberAnimation {
                            id: bar_width_behavior
                            duration: 1000
                            easing.type: Easing.Linear
                        }
                    }
                    onWidthChanged:
                    {
                        if(width == -15 && initial())
                        {
                            player.play();
                        }
                    }
                    Image
                    {
                        id: timeBubble

                        source: "content/controls/Progress bar - in progress.png"
                    }
                }
                Image
                {
                    id: grid

                    source: "content/controls/Grip.png"
                    x: player.duration > 0 ? getPlayerPosition() : -15
                    anchors.verticalCenter: barBackground.verticalCenter
                    Behavior on x
                    {
                        NumberAnimation {
                            id: grid_x_behavior
                            duration: 1000
                            easing.type: Easing.Linear
                        }
                    }

                }

            }

            Text
            {
                id: video_length
                text: timeConvertor(player.duration)
                color: "white"
                font.pixelSize: 18
                font.family: roboto.name
                x: 1718;
                anchors.verticalCenter: barBackground.verticalCenter

            }

            Text
            {
                id: actual_time
                text: timeConvertor(player.position)
                color: "white"
                font.pixelSize: 18
                font.family: roboto.name
                x: 370;
                anchors.verticalCenter: barBackground.verticalCenter
            }
        }

        Text
        {
            id: now_watching
            text: "NOW PLAYING"
            color: "#e56c00"
            font.capitalization: Font.AllUppercase
            font.pixelSize: 18
            font.family: roboto.name
            x: 456; y: 997
            opacity: audioTitle == "" ? 0.0: 1.0
            Behavior on width
            {
                NumberAnimation {
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }
        }
        Image
        {
            id: separater
            source: "content/controls/_.png"
            anchors.left: now_watching.right
            anchors.leftMargin: 20
            anchors.top: now_watching.top
            anchors.topMargin: 3
            opacity: audioTitle == "" ? 0.0: 1.0
            Behavior on width
            {
                NumberAnimation {
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }
        }
        Text
        {
            id: audio_title
            text: audioTitle
            color: "white"
            font.pixelSize: 18
            font.capitalization: Font.AllUppercase
            font.family: roboto.name
            anchors.left: separater.right
            anchors.leftMargin: 20
            anchors.top: now_watching.top
            opacity: audioTitle == "" ? 0.0: 1.0
            Behavior on width
            {
                NumberAnimation {
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }
        }

        Image
        {
            id: playButton

            visible: true

            source: "content/controls/BTN_Play.png"
            width:75; height: 75

            x: 183
            y: 988

            MultiPointTouchArea
            {
                anchors.fill: playButton

                enabled: playButton.visible

                onPressed:
                {
                    playButton.visible = false;

                    console.log("press play button");
                    player.play()

                    stopButton.visible = true;

                    if(player.status === MediaPlayer.EndOfMedia)
                    {
                        bar_width_behavior.duration = 10;
                        grid_x_behavior.duration = 10;
                    }
                }
            }
        }

        Image
        {
            id: stopButton

            visible: false

            source: "content/controls/pause.png"

            x: 183
            y: 988

            MultiPointTouchArea
            {
                anchors.fill: stopButton

                enabled: true

                onPressed:
                {
                    console.log("pause video!!")
                    root.pauseAudio();
                }
            }
        }

        MultiPointTouchArea
        {
            property real seekTo: -1
            property bool release: true


            id: timeScrub

            x: barBackground.x
            y: buttonsBackground.y
            width: barBackground.width
            height: 96

            enabled: player.status != MediaPlayer.Stalled

            // Vertically align to timeBubble with some forgiveness
            onPressed:
            {
                bar_width_behavior.duration = 10;
                grid_x_behavior.duration = 10;
                seekTo = Math.min(player.duration * (touchPoints[0].x / width),player.duration * 0.98);
                player.pause();
                console.log("pressed!")
                player.volume = 0
                timeScrub.release = false;
            }

            onUpdated:
            {
                seekTo = Math.min(player.duration * (touchPoints[0].x / width),player.duration * 0.98);
                console.log("updated!")
                timeScrub.release = false;
            }

            onReleased:
            {
                bar_width_behavior.duration = 1000;
                grid_x_behavior.duration = 1000;
                seekTo = Math.min(player.duration * (touchPoints[0].x / width),player.duration * 0.98);
                console.log("released!")
                timeScrub.release = true;

                seek_timer.restart();

            }

            Timer
            {
                id: seek_timer
                interval: 100
                running: true
                repeat: true
                onTriggered:
                {
                    if (timeScrub.seekTo != -1)
                    {
                        player.seek(timeScrub.seekTo);
                        timeScrub.seekTo = -1;
                        player.play();

                        if(timeScrub.release)
                        {
                            player.volume = 1.0;
                            stopButton.visible = true;

                            playButton.visible = false;
                        }
                    }
                }
            }
        }
    }

    //=========================================================================
    // FUNCTIONS
    //=========================================================================
    onAudioFilepathChanged:
    {
        if(audioFilepath === "")
        {
            player.source = "";
            return;
        }

        player.source = audioFilepath;
        bar_width_behavior.duration = 10;
        grid_x_behavior.duration = 10;
    }

    onAutoPlayChanged:
    {
        initial();
    }

    function pauseAudio()
    {
        stopButton.visible = false;

        playButton.visible = true;

        player.pause();
    }

    function hide()
    {
        stopButton.visible = false;
        playButton.visible = true;
        console.log("hide!!")

        player.pause();

    }


    function initial()
    {
        console.log("initial!! audioFilepath = ", audioFilepath);
        if(root.autoPlay)
        {
            playButton.visible = false;
            bar_width_behavior.duration = 1000;
            grid_x_behavior.duration = 1000;
            player.seek(0);

            stopButton.visible = true;

            controls_dock.y = 0;
            controls_dock.opacity = 1;

            return true
        }
        else
        {
            stopButton.visible = false;
            playButton.visible = true;

            return false
        }
    }

    function reset()
    {
        playButton.visible = false;
        stopButton.visible = true;
    }


    function getPlayerPosition()
    {
        var pos = parseFloat(player.position);
        var dur = parseFloat(player.duration);

        return (pos / dur) * barBackground.width - 15;//total width depends on image width
    }

    function timeConvertor(duration)
    {
        var s = parseInt(duration / 1000);
        var m = parseInt(s / 60);
        s = s - (m * 60);
        if(s < 10)
        {
            s = "0" + s;
        }
        if(m < 10)
        {
            m = "0" + m;
        }

        return m + ":" + s;
    }

    function showPlaying()
    {
        root.visible = true;
        console.log("showPlaying!");
        reset();
        player.play();
    }

}


