#include "qxmlhelper.h"
#include "imagehelper.h"

using namespace Core;
using namespace Platform;

bool QXMLHelper::writeTransformAttribute(QXmlStreamWriter &xml_writer, QTransform transform)
{
	xml_writer.writeAttribute("m11", QString::number(transform.m11()));
	xml_writer.writeAttribute("m12", QString::number(transform.m12()));
	xml_writer.writeAttribute("m13", QString::number(transform.m13()));
	xml_writer.writeAttribute("m21", QString::number(transform.m21()));
	xml_writer.writeAttribute("m22", QString::number(transform.m22()));
	xml_writer.writeAttribute("m23", QString::number(transform.m23()));
	xml_writer.writeAttribute("m31", QString::number(transform.m31()));
	xml_writer.writeAttribute("m32", QString::number(transform.m32()));
	xml_writer.writeAttribute("m33", QString::number(transform.m33()));

	return true;
}

QTransform QXMLHelper::readTransformAttribute(QXmlStreamReader &xml_reader)
{
	const double m11 = xml_reader.attributes().value("m11").toString().toDouble();
	const double m12 = xml_reader.attributes().value("m12").toString().toDouble();
	const double m13 = xml_reader.attributes().value("m13").toString().toDouble();
	const double m21 = xml_reader.attributes().value("m21").toString().toDouble();
	const double m22 = xml_reader.attributes().value("m22").toString().toDouble();
	const double m23 = xml_reader.attributes().value("m23").toString().toDouble();
	const double m31 = xml_reader.attributes().value("m31").toString().toDouble();
	const double m32 = xml_reader.attributes().value("m32").toString().toDouble();
	const double m33 = xml_reader.attributes().value("m33").toString().toDouble();

	QTransform transform;
	transform.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);

	return transform;
}

bool QXMLHelper::writePixmapAttribute(QXmlStreamWriter &xml_writer, QPixmap pixmap, QString name)
{
	xml_writer.writeAttribute(name, ImageHelper::pixmapToPngString(pixmap));

	return !pixmap.isNull();
}

QPixmap QXMLHelper::readPixmapAttribute(QXmlStreamReader &xml_reader, QString name)
{
	return ImageHelper::pngStringToPixmap(xml_reader.attributes().value(name).toString());
}