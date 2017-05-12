#pragma once

#include <QObject>
#include <QList>
#include <QMap>

struct EntryDataSong
{
    int id;
    QString song_name;
    QString artist;
    QString duration;
    QString price;
    QString preview;
    QString image_source;
};


class EntryManager : public QObject
{
    Q_OBJECT
public:

    explicit EntryManager(QObject *parent = 0);

    void addSong(EntryDataSong *entry_song);

    Q_INVOKABLE int getEntriesCount() const;

    Q_INVOKABLE QString getEntrySongName(int index) const;

    Q_INVOKABLE QString getEntryArtist(int index) const;

    Q_INVOKABLE QString getEntryDuration(int index) const;

    Q_INVOKABLE QString getEntryPrice(int index) const;

    Q_INVOKABLE QString getEntryPreview(int index) const;

    Q_INVOKABLE QString getEntryImageSrc(int index) const;

private:

    int m_id;

    QList<EntryDataSong*> m_entries;
};


