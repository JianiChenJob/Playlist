#pragma once

#include <QObject>
#include <QFile>
#include <QPixmap>
#include <QThread>

namespace Platform
{
    class FileReader : public QObject
    {
        Q_OBJECT

    public:
        FileReader();

        void loadImage(const QString& file_path);

        void copyImage(QPixmap image, const QString& destination);

        void copyFile(QString source, QString destination);

    signals:

        void imageLoadFinished(bool success, QPixmap image);

        void imageCopyFinished(bool success, QString destination_file_path);

        void fileCopyFinished(bool success, QString destination_file_path);

    private slots:

        void imageLoadFinishedEventReceived(bool success, QPixmap image);

        void imageCopyFinishedEventReceived(bool success, QString destination_file_path);

        void fileCopyFinishedEventReceived(bool success, QString destination_file_path);
    };

    class ImageCopierThread : public QThread
    {
        Q_OBJECT

    public:

        ImageCopierThread(QPixmap source_pixmap, QString destinatation);

        void run() Q_DECL_OVERRIDE
        {
            bool success = copyToDestination();

            emit imageCopyFinished(success, m_destination);
        }

    signals:

        void imageCopyFinished(bool success, QString destination);

    private:

        bool copyToDestination();

        QPixmap m_source_pixmap;

        QString m_destination;
    };

    class FileCopierThread : public QThread
    {
        Q_OBJECT

    public:

        FileCopierThread(QString source, QString destination);

        void run() Q_DECL_OVERRIDE
        {
            bool success = copyToDestination();

            emit fileCopyFinished(success, m_destination);
        }

    signals:

        void fileCopyFinished(bool success, QString destination);

    private:

        bool copyToDestination();

        QString m_source;
        QString m_destination;
    };

    class ImageReaderThread : public QThread
    {
        Q_OBJECT

    public:

        ImageReaderThread(const QString& file_path);

        void run() Q_DECL_OVERRIDE
        {
            bool success = loadImage();

            emit imageLoadFinished(success, m_image);
        }

    signals:
        void imageLoadFinished(bool success, QPixmap image);

    private:

        bool loadImage();

        QString m_file_path;

        QPixmap m_image;
    };
}
