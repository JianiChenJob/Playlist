#pragma once

#include "tinyxml2/tinyxml2.h"
#include <QString>

namespace Core
{
    class XMLLoader
    {
    public:

		bool parseFile(QString xml_path);

        bool parseFileContents(QString contents);

        virtual bool parseDoc(tinyxml2::XMLDocument& doc) = 0;

    protected:

        QString m_file_path;
    };
}
