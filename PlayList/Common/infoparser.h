#pragma once

#include <QString>
#include <vector>

class InfoParser
{
protected:

    static std::vector<std::vector<QString> > parseCsv(QString file_path);

    static std::vector<std::vector<QString> > parseCsvContents(QString contents);

    static QString readFile(const QString& filename, bool utf8);

    static bool readFileAndPath(QString file_path, QString& contents);
};
