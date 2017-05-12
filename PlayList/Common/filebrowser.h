#pragma once

#include <QString>
#include <iostream>
#include <vector>

namespace Platform
{
    class FileBrowser
    {
    public:

		static QString openFile(const QString& file_types, QString header_text = "Open File");

		static std::vector<QString> openFiles(const QString& file_types, QString header_text = "Open Files");

        static QString saveFileName(const QString& file_types);

		static QString getDirectory(QString default_folder = "", QString localized_string = "Choose Directory");
    };
}
