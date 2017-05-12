import QtQuick 2.5


Item
{
    id: root

    //source: "content/scroll-bar.png"

    //height: scrollLength

    property double scrollLength: 133 - 45

    signal scrollChanged(double percent);

    Item
    {
        x: 1.5; y: 1

        Image
        {
            id: scroller

            source: "content/scroll-bar.png"

            MultiPointPinchArea
            {
                x: -20
                width: parent.width + 40
                height: parent.height
                mouseEnabled: true

                Rectangle
                {
                    anchors.fill: parent
                    visible: false // parent.enabled
                    opacity: 0.7
                    color: 'red'
                }

                onPositionUpdated:
                {
                    var newY = scroller.y + delta_y;
                    if(newY < 0) newY = 0;
                    if(newY > root.scrollLength) newY = root.scrollLength;

                    scroller.y = newY;

                    root.scrollChanged(scroller.y / root.scrollLength);
                }
            }
        }
    }

    function updateBar(percent)
    {
        var newY = percent * root.scrollLength;
        if(newY < 0) newY = 0;
        if(newY > root.scrollLength) newY = root.scrollLength;

        scroller.y = newY;
    }
}
