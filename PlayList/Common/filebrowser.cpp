#include "filebrowser.h"

#include <QFileDialog>
#include <QString>
#include <QStandardPaths>

using namespace Platform;

QString FileBrowser::openFile(const QString& file_types, QString header_text)
{
    return QFileDialog::getOpenFileName(0, header_text,
                                        QStandardPaths::writableLocation(QStandardPaths::StandardLocation::DocumentsLocation),
                                        file_types);
}

std::vector<QString> FileBrowser::openFiles(const QString& file_types, QString header_text)
{
    QList<QString> files = QFileDialog::getOpenFileNames(0, header_text,
                                                         QStandardPaths::writableLocation(QStandardPaths::StandardLocation::DocumentsLocation),
                                                         file_types);

    std::vector<QString> file_names;

    foreach(QString file, files)
    {
        file_names.push_back(file);
    }

    return file_names;
}

QString FileBrowser::saveFileName(const QString& file_types)
{
    return QFileDialog::getSaveFileName(0, "Save File",
                                        QStandardPaths::writableLocation(QStandardPaths::StandardLocation::DocumentsLocation),
                                        file_types);
}

QString FileBrowser::getDirectory(QString default_folder, QString localized_string)
{
	if (default_folder == "")
	{
        default_folder =
                QStandardPaths::writableLocation(QStandardPaths::StandardLocation::DocumentsLocation);
	}

	return QFileDialog::getExistingDirectory(0, localized_string,
                                             default_folder);
}
