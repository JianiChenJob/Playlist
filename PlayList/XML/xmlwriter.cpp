#include "xmlwriter.h"

#include "stringhelper.h"

using namespace Core;

static QString TAB = "    ";

void XMLWriter::writeXMLHeader(QTextStream& stream)
{
    stream << "<?xml version=\"1.0\"?>" << endl;
}

void XMLWriter::writeCMLStart(QTextStream& stream, bool tuio, bool simulator,
                              const QString& root_content)
{
    stream << "<cml tuio=\"" << QString::fromStdString(StringHelper::boolToString(tuio))
           << "\" simulator=\"" << QString::fromStdString(StringHelper::boolToString(simulator))
           << "\" ";

    if(root_content != "")
    {
        stream << "rootContent=\"" << root_content << "\" ";
    }

    stream << ">" << endl;
}

void XMLWriter::writeCMLEnd(QTextStream& stream)
{
    stream << "</cml>" << endl;
    stream << endl;
}

void XMLWriter::writeStartTag(const QString& tag, int depth, QTextStream& stream)
{
    writeTabs(depth, stream);

    stream << "<" << tag;
}

void XMLWriter::writeEndTag(QTextStream& stream)
{
    stream << ">" << endl;
}

void XMLWriter::writeOpeningTag(const QString& tag, int depth, QTextStream& stream)
{
    writeStartTag(tag, depth, stream);

    writeEndTag(stream);
}

void XMLWriter::writeClosingTag(const QString& tag, int depth, QTextStream& stream)
{
    writeTabs(depth, stream);

    stream << "</" << tag << ">" << endl;
}

void XMLWriter::writeClosingTag(QTextStream& stream)
{
    stream << "/>" << endl;
}

void XMLWriter::writeNewLine(QTextStream& stream)
{
    stream << endl;
}

void XMLWriter::writeValue(const QString& value, QTextStream& stream)
{
    stream << value;
}

void XMLWriter::writeValue(float value, QTextStream& stream)
{
    stream << value;
}

void XMLWriter::writeValue(int value, QTextStream& stream)
{
    stream << value;
}

void XMLWriter::writeValue(bool value, QTextStream& stream)
{
    stream << QString::fromStdString(StringHelper::boolToString(value));
}

void XMLWriter::writeAttribute(const QString& name, const QString& value, QTextStream& stream)
{
    stream << " " << name << "=\"" << value <<"\"";
}

void XMLWriter::writeAttribute(const QString& name, const char* value, QTextStream &stream)
{
    stream << " " << name << "=\"" << value <<"\"";
}

void XMLWriter::writeAttribute(const QString& name, float value, QTextStream& stream)
{
    stream << " " << name << "=\"" << value <<"\"";
}

void XMLWriter::writeAttribute(const QString& name, double value, QTextStream& stream)
{
    stream << " " << name << "=\"" << value <<"\"";
}

void XMLWriter::writeAttribute(const QString& name, int value, QTextStream& stream)
{
    stream << " " << name << "=\"" << value <<"\"";
}

void XMLWriter::writeAttribute(const QString& name, bool value, QTextStream& stream)
{
    stream << " " << name << "=\"" << QString::fromStdString(StringHelper::boolToString(value)) <<"\"";
}

void XMLWriter::writeAttribute(const QVector2D& value, QTextStream& stream, const QString& prefix)
{
    if(prefix == "")
    {
        writeAttribute("x", value.x(), stream);
        writeAttribute("y", value.y(), stream);
    }
    else
    {
        writeAttribute(prefix + "X", value.x(), stream);
        writeAttribute(prefix + "Y", value.y(), stream);
    }
}

void XMLWriter::writeAttribute(const QVector3D& value,
                               QTextStream& stream, const QString& prefix)
{
    if(prefix == "")
    {
        writeAttribute("x", value.x(), stream);
        writeAttribute("y", value.y(), stream);
        writeAttribute("z", value.z(), stream);
    }
    else
    {
        writeAttribute(prefix + "X", value.x(), stream);
        writeAttribute(prefix + "Y", value.y(), stream);
        writeAttribute(prefix + "Z", value.z(), stream);
    }
}

void XMLWriter::writeAttributeColor(const QVector4D& value, QTextStream& stream,
                                    const QString& prefix)
{
    if(prefix == "")
    {
        writeAttribute("r", value.x(), stream);
        writeAttribute("g", value.y(), stream);
        writeAttribute("b", value.z(), stream);
        writeAttribute("a", value.w(), stream);
    }
    else
    {
        writeAttribute(prefix + "R", value.x(), stream);
        writeAttribute(prefix + "G", value.y(), stream);
        writeAttribute(prefix + "B", value.z(), stream);
        writeAttribute(prefix + "A", value.w(), stream);
    }
}

void XMLWriter::writeTag(const QString& tag, int depth,
                    const QString& value, QTextStream& stream)
{
    writeTabs(depth, stream);

    stream << "<" << tag << ">" << value << "</" << tag << ">" << endl;
}

void XMLWriter::writeTag(const QString& tag, int depth,
                    float value, QTextStream& stream)
{
    writeTabs(depth, stream);

    stream << "<" << tag << ">" << value << "</" << tag << ">" << endl;
}

void XMLWriter::writeTag(const QString& tag, int depth,
                    int value, QTextStream& stream)
{
    writeTabs(depth, stream);

    stream << "<" << tag << ">" << value << "</" << tag << ">" << endl;
}

void XMLWriter::writeTag(const QString& tag, int depth,
                     bool value, QTextStream& stream)
{
    writeTabs(depth, stream);

    stream << "<" << tag << ">" << value << "</" << tag << ">" << endl;
}

void XMLWriter::writeTag(const QString& tag, int depth,
                         const QVector2D& value, QTextStream& stream)
{
    writeStartTag(tag, depth, stream);

    writeAttribute(value, stream);

    writeClosingTag(stream);
}

void XMLWriter::writeTag(const QString &tag, int depth,
                     const QVector3D& value, QTextStream& stream)
{
    writeStartTag(tag, depth, stream);

    writeAttribute(value, stream);

    writeClosingTag(stream);
}

void XMLWriter::writeTabs(int depth, QTextStream& stream)
{
    for(int i = 0; i != depth; ++i)
    {
        stream << TAB;
    }
}
