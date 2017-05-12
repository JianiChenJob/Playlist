#include "infoparser.h"

#include <QTextStream>
#include <QFileInfo>
#include <QString>
#include <QMessageBox>
#include <QDebug>

static const QString s_filepath_prefix = "";

std::vector<std::vector<QString> > InfoParser::parseCsv(QString file_path)
{
    QString contents;
    if(readFileAndPath(s_filepath_prefix + file_path, contents))
    {
        return parseCsvContents(contents);
    }
    else
    {
        QMessageBox::warning(nullptr, "Could not find parse CSV", "Could not parse CSV file: " + file_path);
    }

    return std::vector<std::vector<QString> >();
}

std::vector<std::vector<QString> > InfoParser::parseCsvContents(QString contents)
{
    std::vector< std::vector<QString> > line_values;

    QStringList entries = contents.split('\n');
    if (entries.empty())
    {
        return line_values;
    }

    bool first = true;

    for (int i = 0; i != entries.size(); ++i)
    {
        QString entry = entries[i];

        // Skip first
        if (first)
        {
            first = false;
            continue;
        }

        for (unsigned int i = 0; i != entry.size(); ++i)
        {
            QCharRef c = entry[i];
            if (c == '^')
            {
                entry[i] = ' ';
            }
        }

        QStringList values = entry.split('|');
        std::vector<QString> temp_values;
        for (int j = 0; j != values.size(); ++j)
        {
            QString value_entry = values[j].trimmed();
            temp_values.push_back(value_entry);
        }

        line_values.push_back(temp_values);
    }

    return line_values;
}

QString InfoParser::readFile(const QString& filename, bool utf8)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return "";
    }

    QTextStream infile(&file);

    if(utf8)
    {
        infile.setCodec("UTF-8");
    }

    QString file_contents = infile.readAll();

    file.close();

    return file_contents;
}

bool InfoParser::readFileAndPath(QString file_path, QString& contents)
{
    contents = readFile(file_path, true);

    if (contents.isEmpty())
    {
        qDebug() << "Could not read file contents " << file_path;
        return false;
    }

    QFileInfo file_info(file_path);
    if (!file_info.exists())
    {
        qDebug() << "Could not load file " << file_path;
        return false;
    }

    return true;
}
