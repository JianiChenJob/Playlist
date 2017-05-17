/*! list.qml is a play list displaying the top 100 songs from itunes store*/
import QtQuick 2.0

Item
{
    id: root

    property var songs: []

    property int rowSize: 0

    signal songClicked(var preview, var imageSource, var songName, var artist, var duration, var price);

    FontLoader
    {
        id: roboto
        source: "content/Roboto-Regular.ttf"
    }

    Item
    {
        id: title

        height: 63
        width: 1196
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
            id: song_name
            text: "Name"
            color: "#cac6c7"
            font.pixelSize: 20
            x: 40
            anchors.verticalCenter: title.verticalCenter
            font.family: roboto.name
        }
        Text
        {
            id: song_artist
            text: "Artist"
            color: "#cac6c7"
            font.pixelSize: 20
            x: 730
            anchors.verticalCenter: title.verticalCenter
            font.family: roboto.name
        }
        Text
        {
            id: song_duration
            text: "Time"
            color: "#cac6c7"
            font.pixelSize: 20
            x: 730 + 370
            anchors.verticalCenter: title.verticalCenter
            font.family: roboto.name


        }
    }

    ListScrollView
    {
        id: scroll
        width: 1196
        height: 630
        y: 63
        Item
        {
            id: list
            Repeater
            {
                model: entryManager.getEntriesCount()

                SongEntry
                {
                    onSongClicked:root.songClicked(preview, imageSource, songName, artist, duration, price);
                }

                onItemAdded:
                {
                    item.y = heightOffset();
                    item.songName = entryManager.getEntrySongName(index);
                    item.artist = entryManager.getEntryArtist(index);
                    item.duration = root.timeConvertor(entryManager.getEntryDuration(index));
                    item.price = entryManager.getEntryPrice(index);
                    item.preview = entryManager.getEntryPreview(index);
                    item.imageSource = entryManager.getEntryImageSrc(index);
                    item.songID = index + 1;

                    songs.push(item);

                    root.rowSize = item.y + item.height;
                    list.height = root.rowSize;
                    //console.log("item.imageSource = ", item.imageSource)
                }
            }
        }
        flickableItem.onContentYChanged:
        {
            //image_timer.restart();
            scroll_bar.updateBar(flickableItem.contentY / (flickableItem.contentHeight - flickableItem.height));
        }
    }
    ScrollBar
    {
        id: scroll_bar

        //x: (scroll_bkg.width * root.scale - 15)
        scrollLength: scroll.height - 133
        anchors.left: scroll.right
        y: 63

        //transform: Scale { xScale: 1.0 / root.scale; yScale: 1.0 / root.scale }

        onScrollChanged:
        {
            scroll.flickableItem.contentY = percent * (scroll.flickableItem.contentHeight - scroll.flickableItem.height);
        }
    }


    function heightOffset()
    {
        var offset = 0.0;
        for(var i = 0; i < songs.length; i++)
        {
            offset += songs[i].height// + root.rowSpacing;
        }
        return offset;
    }

    function activatePlayingSong(audioFilepath, active)
    {
        for(var i = 0; i < songs.length; i++)
        {
            if(songs[i].preview == audioFilepath)
            {
                songs[i].playing(active);
            }
        }
    }
    function switchPlayingSong()
    {
        for(var i = 0; i < songs.length; i++)
        {
             songs[i].playing(false);
        }
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
}
