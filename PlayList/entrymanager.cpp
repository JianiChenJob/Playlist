#include "entrymanager.h"

#include <QDebug>
#include <QDir>

EntryManager::EntryManager(QObject *parent) : QObject(parent)
{

}

void EntryManager::addSong(EntryDataSong *entry_song)
{
    m_entries.append(entry_song);
}

int EntryManager::getEntriesCount() const
{
    return m_entries.size();
}

QString EntryManager::getEntrySongName(int index) const
{
    if(index < 0 || index >= m_entries.size())
    {
        return "";
    }
    return m_entries[index]->song_name;
}

QString EntryManager::getEntryArtist(int index) const
{
    if(index < 0 || index >= m_entries.size())
    {
        return "";
    }
    return m_entries[index]->artist;
}

QString EntryManager::getEntryDuration(int index) const
{
    if(index < 0 || index >= m_entries.size())
    {
        return "";
    }
    return m_entries[index]->duration;
}

QString EntryManager::getEntryPrice(int index) const
{
    if(index < 0 || index >= m_entries.size())
    {
        return "";
    }
    return m_entries[index]->price;
}

QString EntryManager::getEntryPreview(int index) const
{
    if(index < 0 || index >= m_entries.size())
    {
        return "";
    }
    return m_entries[index]->preview;
}

QString EntryManager::getEntryImageSrc(int index) const
{
    if(index < 0 || index >= m_entries.size())
    {
        return "";
    }
    return m_entries[index]->image_source;
}
