#pragma once

#include <string>
#include <vector>
#include <QString>

namespace Platform
{
    class FileHelper
    {
    public:

        static void readBinaryFile(const QString& filename, std::vector<char>& data);

        static QString readFile(const QString& filename, bool utf8 = false);

        static bool fileExists(const QString& filename);

		static bool fileIsFolder(const QString& filename);

        static unsigned char* loadImage(const QString& filename,
                                             int *width, int *height, int *channels);

		static std::vector<QString> findAllFoldersTime(const QString& directory_path, bool recursive, QString folder_name = "");

		static std::vector<QString> findAllFolders(const QString& directory_path, bool recursive = false, QString folder_name = "");

		static std::vector<QString> findAllFiles(const QString& directory_path, bool recursive = false, QString file_extension = "");

		static bool removeFile(QString file_path);

		static bool removeFolder(QString directory_path);

		static bool copyDir(QString source_path, QString destination_path, bool overwrite = true);
    };
}
