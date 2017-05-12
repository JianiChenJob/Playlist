#pragma once

#include <iostream>
#include <vector>
#include <QColor>

namespace Core
{
    class StringHelper
    {
    public:
        static std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems, bool include_empties = false);

        static std::vector<std::string> split(const std::string &s, char delim, bool include_empties = false);

        static std::string getLastSplit(const std::string &s, char delim);

        static std::string trim(const std::string& s);

        static std::string trim(const std::string &s, char element);

        static std::string trim(const std::string &s, const std::vector<char>& elements);

        static std::string trimWhitespace(const std::string& s);

        static std::string removeChar(const std::string& s, char c);

        static std::string replace(const std::string &s, const std::string& from, const std::string& to);

        static bool contains(const std::string& s, const std::string& substring);

        static std::string toLower(const std::string& s);

        static std::string toUpper(const std::string& s);

        static int stringToInt(const std::string& s);

		static int stringToInt(char c);

        static std::string boolToString(bool value);

        static std::string intToString(int value);
        
        static int hexStringToInt(const std::string& s);

        static std::string doubleToString(double value);

        static double stringToDouble(const std::string& s);

        static float stringToFloat(const std::string& s);

        static std::string floatToString(float value);

        static bool stringToBool(const std::string& s);

        static bool hexStringToColorFloat(const std::string& color_string, float &r, float &g, float &b);

        static bool hexStringToColor(const std::string& color_string, int &r, int &g, int &b);

		static bool hexStringToColor(const std::string& color_string, QColor &color);

        static int hexCharToInt(char c);

        static std::string switchDirSeperatorsToMac(const std::string& s);

        static std::string toTimeString(double time);

		static std::string toTimeString(int time);
    };

}
