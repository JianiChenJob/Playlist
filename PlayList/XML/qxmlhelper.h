#pragma once

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTransform>

namespace Core
{
	class QXMLHelper
	{
	public:

		static bool writeTransformAttribute(QXmlStreamWriter &xml_writer, QTransform transform);
	
		static QTransform readTransformAttribute(QXmlStreamReader &xml_reader);

		static bool writePixmapAttribute(QXmlStreamWriter &xml_writer, QPixmap pixmap, QString name = "image");
	
		static QPixmap readPixmapAttribute(QXmlStreamReader &xml_reader, QString name = "image");
	};
}