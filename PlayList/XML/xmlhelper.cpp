#include "xmlhelper.h"

#include "stringhelper.h"
#include "filehelper.h"
#include <QString>

using namespace Core;
using namespace Platform;
using namespace tinyxml2;

std::string XMLHelper::attributeToString(XMLNode *node, const std::string& attr_name)
{
    if(!node)
    {
        return "";
    }

    XMLElement*	node_element = node->ToElement();
    if(!node_element)
    {
        return "";
    }

    const char *attr = node_element->Attribute(attr_name.c_str());
    if(attr)
    {
        return StringHelper::trimWhitespace(std::string(attr));
    }

    return "";
}

QString XMLHelper::attributeToQString(XMLNode *node, const std::string& attr_name)
{
    if(!node)
    {
        return "";
    }

    XMLElement*	node_element = node->ToElement();
    if(!node_element)
    {
        return "";
    }

    const char *attr = node_element->Attribute(attr_name.c_str());
    if(attr)
    {
        QString qattr(attr);
        return qattr.trimmed();
    }

    return "";
}

float XMLHelper::attributeToFloat(XMLNode *node, const std::string& attr_name)
{
    if(!node)
    {
        return 0.0f;
    }

    XMLElement*	node_element = node->ToElement();
    if(!node_element)
    {
        return 0.0f;
    }

    const char *float_attr = node_element->Attribute(attr_name.c_str());
    if(float_attr)
    {
        std::string value(float_attr);
        return StringHelper::stringToFloat(value);
    }

    return 0.0f;
}

int XMLHelper::attributeToInt(XMLNode *node, const std::string& attr_name)
{
    if(!node)
    {
        return 0;
    }

    XMLElement*	node_element = node->ToElement();
    if(!node_element)
    {
        return 0;
    }

    const char *int_attr = node_element->Attribute(attr_name.c_str());
    if(int_attr)
    {
        std::string value(int_attr);
        return StringHelper::stringToInt(value);
    }

    return 0;
}

bool XMLHelper::attributeToBool(XMLNode *node, const std::string &attr_name)
{
    if(!node)
    {
        return false;
    }

    XMLElement*	node_element = node->ToElement();
    if(!node_element)
    {
        return false;
    }

    const char *bool_attr = node_element->Attribute(attr_name.c_str());
    if(bool_attr)
    {
        std::string value(bool_attr);
        return StringHelper::stringToBool(value);
    }

    return false;
}

QVector2D XMLHelper::attributeToVec2(XMLNode *node, const std::string& attr_name)
{
    if(!node)
    {
        return QVector2D(0.0f, 0.0f);
    }

    XMLElement*	node_element = node->ToElement();
    if(!node_element)
    {
        return QVector2D(0.0f, 0.0f);
    }

    const char *vec_attr = node_element->Attribute(attr_name.c_str());
    if(vec_attr)
    {
        std::string value = StringHelper::removeChar(vec_attr, ' ');

        std::vector<std::string> values = StringHelper::split(value, ',');

        if(values.size() != 2)
        {
            return QVector2D(0.0f, 0.0f);
        }

        QVector2D v;
        v.setX(StringHelper::stringToFloat(values[0]));
        v.setY(StringHelper::stringToFloat(values[1]));

        return v;
    }

    return QVector2D(0.0f, 0.0f);
}

QVector3D XMLHelper::attributeToVec3(XMLNode *node, const std::string& attr_name)
{
    if(!node)
    {
        return QVector3D(0.0f, 0.0f, 0.0f);
    }

    XMLElement*	node_element = node->ToElement();
    if(!node_element)
    {
        return QVector3D(0.0f, 0.0f, 0.0f);
    }

    const char *vec_attr = node_element->Attribute(attr_name.c_str());
    if(vec_attr)
    {
        std::string value = StringHelper::removeChar(vec_attr, ' ');

        std::vector<std::string> values = StringHelper::split(value, ',');

        if(values.size() != 3)
        {
            return QVector3D(0.0f, 0.0f, 0.0f);
        }

        QVector3D v;
        v.setX(StringHelper::stringToFloat(values[0]));
        v.setY(StringHelper::stringToFloat(values[1]));
        v.setZ(StringHelper::stringToFloat(values[2]));

        return v;
    }

    return QVector3D(0.0f, 0.0f, 0.0f);
}

float XMLHelper::nodeToFloat(XMLNode *node, const std::string& child_name)
{
    XMLElement *float_node = getChild(node, child_name);
    if(!float_node)
    {
        return 0.0f;
    }

    return StringHelper::stringToFloat(float_node->GetText());
}

QVector2D XMLHelper::nodeToVec2(XMLNode *node, const std::string& vector_name)
{
    if(!node)
    {
        return QVector2D(0.0f, 0.0f);
    }

    XMLElement *vector_node = getChild(node, vector_name);
    if(!vector_node)
    {
        return QVector2D(0.0f, 0.0f);
    }

    QVector2D v;
    v.setX(XMLHelper::attributeToFloat(vector_node, "x"));
    v.setY(XMLHelper::attributeToFloat(vector_node, "y"));

    return v;
}

QVector3D XMLHelper::nodeToVec3(XMLNode *node, const std::string& vector_name)
{
    if(!node)
    {
        return QVector3D(0.0f, 0.0f, 0.0f);
    }

    XMLElement *vector_node = getChild(node, vector_name);
    if(!vector_node)
    {
        return QVector3D(0.0f, 0.0f, 0.0f);
    }

    QVector3D v;
    v.setX(XMLHelper::attributeToFloat(vector_node, "x"));
    v.setY(XMLHelper::attributeToFloat(vector_node, "y"));
    v.setZ(XMLHelper::attributeToFloat(vector_node, "z"));

    return v;
}

QVector4D XMLHelper::nodeToVec4(XMLNode *node, const std::string& vector_name)
{
    if(!node)
    {
        return QVector4D(0.0f, 0.0f, 0.0f, 0.0f);
    }

    XMLElement *vector_node = getChild(node, vector_name);
    if(!vector_node)
    {
        return QVector4D(0.0f, 0.0f, 0.0f, 0.0f);
    }

    QVector4D v;
    v.setX(XMLHelper::attributeToFloat(vector_node, "x"));
    v.setY(XMLHelper::attributeToFloat(vector_node, "y"));
    v.setZ(XMLHelper::attributeToFloat(vector_node, "z"));
    v.setW(XMLHelper::attributeToFloat(vector_node, "w"));

    return v;
}

QVector4D XMLHelper::nodeToColor(XMLNode *node, const std::string& color_name)
{
    if(!node)
    {
        return QVector4D(0.0f, 0.0f, 0.0f, 0.0f);
    }

    XMLElement *color_node = getChild(node, color_name);
    if(!color_node)
    {
        return QVector4D(0.0f, 0.0f, 0.0f, 0.0f);
    }

    QVector4D c;
    c.setX(XMLHelper::attributeToFloat(color_node, "r") / 255.0f);
    c.setY(XMLHelper::attributeToFloat(color_node, "g") / 255.0f);
    c.setZ(XMLHelper::attributeToFloat(color_node, "b") / 255.0f);

    if(hasAttribute(color_node, "a"))
    {
        c.setW(XMLHelper::attributeToFloat(color_node, "a") / 255.0f);
    }
    else
    {
        c.setW(1.0f);
    }

    return c;
}

bool XMLHelper::hasAttribute(XMLNode *node, const std::string& attr_name)
{
    if(!node)
    {
        return false;
    }

    XMLElement*	node_element = node->ToElement();
    if(!node_element)
    {
        return false;
    }

    const char *attr = node_element->Attribute(attr_name.c_str());
    if(!attr)
    {
        return false;
    }

    return true;
}

std::string XMLHelper::childToString(XMLNode *node, const std::string& child_name)
{
    if(!node)
    {
        return "";
    }

    XMLElement *child_element = node->FirstChildElement(child_name.c_str());

    if(!child_element || !child_element->GetText())
    {
        return "";
    }

    std::string text(child_element->GetText());

    return StringHelper::trimWhitespace(text);
}

QString XMLHelper::childToQString(XMLNode *node, const std::string& child_name)
{
    if(!node)
    {
        return "";
    }

    XMLElement *child_element = node->FirstChildElement(child_name.c_str());

    if(!child_element || !child_element->GetText())
    {
        return "";
    }

    QString text(child_element->GetText());

    return text.trimmed();
}

bool XMLHelper::childToBool(XMLNode *node, const std::string& child_name)
{
    if(!node)
    {
        return false;
    }

    std::string text = childToString(node, child_name);
    if(text == "")
    {
        return false;
    }

    return StringHelper::stringToBool(text);
}

int XMLHelper::childToInt(XMLNode *node, const std::string& child_name)
{
    if(!node)
    {
        return 0;
    }

    std::string text = childToString(node, child_name);

    if(text == "")
    {
        return 0;
    }

    return StringHelper::stringToInt(text);
}

float XMLHelper::childToFloat(XMLNode *node, const std::string& child_name)
{
    if(!node)
    {
        return 0.0f;
    }

    std::string text = childToString(node, child_name);

    if(text == "")
    {
        return 0.0f;
    }

    return StringHelper::stringToFloat(text);
}

XMLElement* XMLHelper::getChild(XMLNode *node, const std::string& child_name)
{
    if(!node)
    {
        return nullptr;
    }

    std::vector<XMLElement*> elements = getChildrenNamed(node, child_name);
    if(elements.empty())
    {
        return nullptr;
    }

    return elements[0];
}

std::vector<XMLElement*> XMLHelper::getChildren(XMLNode *node)
{
    std::vector<XMLElement*> elements;

    if(!node)
    {
        return elements;
    }

    for(XMLNode *child_node = node->FirstChild();
        child_node; child_node = child_node->NextSibling())
    {
        XMLElement *child_element = child_node->ToElement();
        if(!child_element)
        {
            continue;
        }

        elements.push_back(child_element);
    }

    return elements;
}

std::vector<XMLElement*> XMLHelper::getChildrenNamed(XMLNode *node, const std::string& child_name)
{
    std::vector<XMLElement*> elements;

    if(!node)
    {
        return elements;
    }

    for(XMLNode *child_node = node->FirstChild();
        child_node; child_node = child_node->NextSibling())
    {
        XMLElement *child_element = child_node->ToElement();
        if(!child_element)
        {
            continue;
        }

        const std::string node_name = std::string(child_element->Name());
        if(node_name == child_name)
        {
            elements.push_back(child_element);
        }
    }

    return elements;
}
XMLNode* XMLHelper::loadXMLFile(const QString& file_path, const std::string& root_node_name,
                                tinyxml2::XMLDocument &doc)
{
    if(!FileHelper::fileExists(file_path))
    {
        return nullptr;
    }

    QString content = FileHelper::readFile(file_path);
    if(content.isEmpty())
    {
        return nullptr;
    }

    doc.Parse(content.toStdString().c_str());

    return doc.FirstChildElement(root_node_name.c_str());
}
