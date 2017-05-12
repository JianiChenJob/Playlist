#pragma once

#include <QString>
#include <string>

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

#include "tinyxml2/tinyxml2.h"

namespace Core
{
    class XMLHelper
    {
    public:
          static std::string attributeToString(tinyxml2::XMLNode *node, const std::string& attr_name);

          static QString attributeToQString(tinyxml2::XMLNode *node, const std::string& attr_name);

          static int attributeToInt(tinyxml2::XMLNode *node, const std::string& attr_name);

          static bool attributeToBool(tinyxml2::XMLNode *node, const std::string &attr_name);

          static float attributeToFloat(tinyxml2::XMLNode *node, const std::string& attr_name);

          static QVector2D attributeToVec2(tinyxml2::XMLNode *node, const std::string& attr_name);

          static QVector3D attributeToVec3(tinyxml2::XMLNode *node, const std::string& attr_name);

          static float nodeToFloat(tinyxml2::XMLNode *node, const std::string& child_name);

          static QVector2D nodeToVec2(tinyxml2::XMLNode *node, const std::string& child_vector_name);

          static QVector3D nodeToVec3(tinyxml2::XMLNode *node, const std::string& child_vector_name);

          static QVector4D nodeToVec4(tinyxml2::XMLNode *node, const std::string& child_vector_name);

          static QVector4D nodeToColor(tinyxml2::XMLNode *node, const std::string& child_color_name);

          static bool hasAttribute(tinyxml2::XMLNode *node, const std::string& attr_name);

          static std::string childToString(tinyxml2::XMLNode *node, const std::string& child_name);

          static QString childToQString(tinyxml2::XMLNode *node, const std::string& child_name);

          static bool childToBool(tinyxml2::XMLNode *node, const std::string& child_name);

          static int childToInt(tinyxml2::XMLNode *node, const std::string& child_name);

          static float childToFloat(tinyxml2::XMLNode *node, const std::string& child_name);

          static tinyxml2::XMLElement* getChild(tinyxml2::XMLNode *node, const std::string& child_name);

          static std::vector<tinyxml2::XMLElement*> getChildren(tinyxml2::XMLNode *node);

          static std::vector<tinyxml2::XMLElement*> getChildrenNamed(tinyxml2::XMLNode *node, const std::string& child_name);

          static tinyxml2::XMLNode* loadXMLFile(const QString& file_path, const std::string& root_node_name,
                                                tinyxml2::XMLDocument &doc);
    };
}
