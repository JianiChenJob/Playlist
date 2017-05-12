#include "xmlloader.h"

#include "filehelper.h"

#include <QMessageBox>
#include <QString>
#include <QDebug>

using namespace tinyxml2;
using namespace Core;
using namespace Platform;

bool XMLLoader::parseFile(QString xml_path)
{
    m_file_path = xml_path;

    QString contents = FileHelper::readFile(m_file_path);

    const bool success_parsing = parseFileContents(contents);

    if(!success_parsing)
    {
        qDebug() << "Bad XML Contents: " << contents;

        QMessageBox::warning(0, "Error",
                             "Error loading xml file: " + m_file_path);
        return false;
    }

    return true;
}

bool XMLLoader::parseFileContents(QString contents)
{
    if(contents == "")
    {
        return false;
    }

    XMLDocument doc;
    doc.Parse(contents.toStdString().c_str());

    return parseDoc(doc);
}

