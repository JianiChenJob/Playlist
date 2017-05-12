#pragma once

#include <QTextStream>

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

namespace Core
{
    class XMLWriter
    {
    public:

        static void writeXMLHeader(QTextStream& stream);

        static void writeCMLStart(QTextStream& stream, bool tuio, bool simulator,
                                  const QString& root_content);

        static void writeCMLEnd(QTextStream& stream);

        static void writeStartTag(const QString& tag, int depth, QTextStream& stream);

        static void writeEndTag(QTextStream& stream);

        static void writeOpeningTag(const QString& tag, int depth, QTextStream& stream);

        static void writeClosingTag(const QString& tag, int depth, QTextStream& stream);

        static void writeClosingTag(QTextStream& stream);

        static void writeNewLine(QTextStream& stream);

        static void writeValue(const QString& value, QTextStream& stream);

        static void writeValue(float value, QTextStream& stream);

        static void writeValue(int value, QTextStream& stream);

        static void writeValue(bool value, QTextStream& stream);

        static void writeAttribute(const QString& name, const QString& value, QTextStream& stream);

        static void writeAttribute(const QString& name, const char* value, QTextStream &stream);

        static void writeAttribute(const QString& name, float value, QTextStream& stream);

        static void writeAttribute(const QString& name, double value, QTextStream& stream);

        static void writeAttribute(const QString& name, int value, QTextStream& stream);

        static void writeAttribute(const QString& name, bool value, QTextStream& stream);

        static void writeAttribute(const QVector2D& value, QTextStream& stream, const QString& prefix = "");

        static void writeAttribute(const QVector3D& value, QTextStream& stream, const QString& prefix = "");

        static void writeAttributeColor(const QVector4D& value, QTextStream& stream, const QString& prefix = "");

        static void writeTag(const QString& tag, int depth,
                             const QString& value, QTextStream& stream);

        static void writeTag(const QString& tag, int depth,
                             float value, QTextStream& stream);

        static void writeTag(const QString& tag, int depth,
                             int value, QTextStream& stream);

        static void writeTag(const QString& tag, int depth,
                             bool value, QTextStream& stream);

        static void writeTag(const QString& tag, int depth,
                             const QVector2D& value, QTextStream &stream);

        static void writeTag(const QString& tag, int depth,
                             const QVector3D& value, QTextStream& stream);

    private:
        static void writeTabs(int depth, QTextStream& stream);
    };
}
