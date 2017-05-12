#include "xmlparser.h"

#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

#include "xmlhelper.h"

using namespace Core;
using namespace tinyxml2;

XMLParser::XMLParser()
{

}

bool XMLParser::parseEntries(EntryManager *entry_manager, QString filepath)
{
    if(!entry_manager)
    {
        return false;
    }

    XMLDocument doc;
    doc.LoadFile(filepath.toStdString().c_str());

    XMLElement *root_node = doc.RootElement();

    if(!root_node)
    {
        return false;
    }

    std::vector<XMLElement*> entries = XMLHelper::getChildrenNamed(root_node, "entry");
    for(int i = 0; i != entries.size(); ++i)
    {
        XMLElement *entry = entries.at(i);

        EntryDataSong *song = new EntryDataSong;

        song->id = XMLHelper::attributeToInt(XMLHelper::getChild(entry, "id"), "im:id");
        if(XMLElement *song_name = entry->FirstChildElement("im:name"))
        {
            song->song_name = song_name ->GetText();
        }

        if(XMLElement *artist = entry->FirstChildElement("im:artist"))
        {
            song->artist = artist ->GetText();
        }

        std::vector<XMLElement*> link_data = XMLHelper::getChildrenNamed(entry, "link");
        for(int j = 0; j != link_data.size(); ++j)
        {
            XMLElement *link = link_data.at(j);
            if(XMLHelper::hasAttribute(link, "title"))
            {
                song->preview = XMLHelper::attributeToQString(link, "href");

                if(XMLElement *duration = link->FirstChildElement("im:duration"))
                {
                    song->duration = duration ->GetText();
                }
            }
        }

        if(XMLElement *price = entry->FirstChildElement("im:price"))
        {
            song->price = price ->GetText();
        }
        if(XMLElement *image_src = entry->FirstChildElement("im:image"))
        {
            song->image_source= image_src ->GetText();
        }
        //qDebug() << "song "<< i << " song->image_source is "<< song->image_source;
        entry_manager->addSong(song);

    }

    return true;
}
