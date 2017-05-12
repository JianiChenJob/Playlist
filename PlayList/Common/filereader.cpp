#include "filereader.h"

#include <QFileInfo>

using namespace Platform;

FileReader::FileReader()
{
}

void FileReader::loadImage(const QString& file_path)
{
    ImageReaderThread image_reader(file_path);
    connect(&image_reader, &ImageReaderThread::imageLoadFinished,
            this, &FileReader::imageLoadFinishedEventReceived);
}

void FileReader::copyImage(QPixmap image, const QString& destination)
{
    ImageCopierThread *copy_thread = new ImageCopierThread(image, destination);

    connect(copy_thread, &ImageCopierThread::imageCopyFinished,
            this, &FileReader::imageCopyFinished);

    connect(copy_thread, &QThread::finished,
            copy_thread, &QObject::deleteLater);

    copy_thread->start();
}

void FileReader::copyFile(QString source, QString destination)
{
    FileCopierThread *copy_thread = new FileCopierThread(source, destination);

    connect(copy_thread, &FileCopierThread::fileCopyFinished,
            this, &FileReader::fileCopyFinished);

    connect(copy_thread, &QThread::finished,
            copy_thread, &QObject::deleteLater);

    copy_thread->start();
}

void FileReader::imageLoadFinishedEventReceived(bool success, QPixmap image)
{
    emit imageLoadFinished(success, image);
}

void FileReader::imageCopyFinishedEventReceived(bool success, QString destination_file_path)
{
    emit imageCopyFinished(success, destination_file_path);
}

void FileReader::fileCopyFinishedEventReceived(bool success, QString destination_file_path)
{
    emit fileCopyFinished(success, destination_file_path);
}

ImageCopierThread::ImageCopierThread(QPixmap source_pixmap, QString destination) :
    m_source_pixmap(source_pixmap),
    m_destination(destination)
{
}

bool ImageCopierThread::copyToDestination()
{
    if(m_source_pixmap.isNull())
    {
        return false;
    }

    return m_source_pixmap.save(m_destination);
}

FileCopierThread::FileCopierThread(QString source, QString destination) :
    m_source(source),
    m_destination(destination)
{
}

bool FileCopierThread::copyToDestination()
{
    QFileInfo source_info(m_source);
    if(!source_info.exists() || !source_info.isReadable())
    {
        return false;
    }

    return QFile::copy(m_source, m_destination);
}

ImageReaderThread::ImageReaderThread(const QString& file_path)
{
    m_file_path = file_path;
}

bool ImageReaderThread::loadImage()
{
    QFileInfo file_info(m_file_path);
    if(!file_info.exists())
    {
        return false;
    }

    QPixmap image(m_file_path);

    const bool success = !image.isNull();

    m_image = image;

    return success;
}


