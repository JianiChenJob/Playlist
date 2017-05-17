/*! PlayBarsAnimation.qml is when the selected song is playing
there will be three bars animation showing instead of song's number*/
import QtQuick 2.0

Item
{
    property int targetWidth: 5
    Rectangle
    {
        id: bar1
        rotation: 180
        width: 2
        color: "#ffffff"
    }
    Rectangle
    {
        id: bar2
        width: 2
        color: "#ffffff"
        x: 4
    }
    Rectangle
    {
        id: bar3
        width: 2
        color: "#ffffff"
        x: 8
    }
    ParallelAnimation
    {
        id: bars_animation
        NumberAnimation {
            id: bar1_animation
            target: bar1
            property: "height"
            from: 3
            to: 8
            duration: 800
            easing.type: Easing.InOutQuad
            loops: Animation.Infinite
        }

        SequentialAnimation
        {
        PauseAnimation {
            duration: 300
        }
        NumberAnimation {
            id: bar2_animation
            target: bar2
            property: "height"
            from: 3
            to: 8
            duration: 800
            easing.type: Easing.InOutQuad
            loops: Animation.Infinite
        }
        }
        SequentialAnimation
        {
        PauseAnimation {
            duration: 500
        }
        NumberAnimation {
            id: bar3_animation
            target: bar3
            property: "height"
            from: 3
            to: 8
            duration: 800
            easing.type: Easing.InOutQuad
            loops: Animation.Infinite
        }
        }
    }
    function play()
    {
        bars_animation.start();
    }
    Component.onCompleted: play()



}
