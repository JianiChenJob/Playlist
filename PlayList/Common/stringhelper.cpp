#include "stringhelper.h"

#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace Core;

std::vector<std::string> StringHelper::split(const std::string &s, char delim, std::vector<std::string> &elems, bool include_empties)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        if(item.size() > 0 || include_empties)
        {
            elems.push_back(item);
        }
    }
    return elems;
}

std::vector<std::string> StringHelper::split(const std::string &s, char delim, bool include_empties)
{
    std::vector<std::string> elems;
    split(s, delim, elems, include_empties);
    return elems;
}

std::string StringHelper::getLastSplit(const std::string &s, char delim)
{
    std::vector<std::string> elems = split(s, delim);

    if(!elems.empty())
    {
        return elems[elems.size() - 1];
    }

    return "";
}

std::string StringHelper::trim(const std::string& s)
{
    return trim(s, ' ');
}

std::string StringHelper::trim(const std::string &s, char element)
{
    std::vector<char> elements;
    elements.push_back(element);

    return trim(s, elements);
}

std::string StringHelper::trim(const std::string &s, const std::vector<char>&  elements)
{
    const int elem_length = static_cast<int>(elements.size());

    std::string str = s;

    int trim_front_length = 0;
    for(unsigned int i = 0; i != s.size(); ++i)
    {
        bool trim_char = false;
        for(int j = 0; j != elem_length; ++j)
        {
            if(str[i] == elements[j])
            {
                trim_front_length++;
                trim_char = true;
                break;
            }
        }

        if(!trim_char)
        {
            break;
        }
    }

    if(trim_front_length > 0)
    {
        str.erase(str.begin(), str.begin() + trim_front_length);
    }

    if(str.empty())
    {
        return "";
    }

    int trim_back_length = 0;
    for(unsigned int i = str.size() - 1; i != 0; --i)
    {
        bool trim_char = false;
        for(int j = 0; j != elem_length; ++j)
        {
            if(str[i] == elements[j])
            {
                trim_back_length++;
                trim_char = true;
                break;
            }
        }

        if(!trim_char)
        {
            break;
        }
    }

    if(trim_back_length > 0)
    {
        str.erase(str.end() - trim_back_length, str.end());
    }

    return str;
}

std::string StringHelper::trimWhitespace(const std::string& s)
{
    std::vector<char> elements;
    elements.push_back(' ');
    elements.push_back('\n');
    elements.push_back('\t');

    return trim(s, elements);
}

std::string StringHelper::removeChar(const std::string& s, char c)
{
    std::stringstream stream;

    for(unsigned int i = 0; i != s.size(); ++i)
    {
        char value = s[i];
        if(value != c)
        {
            stream << value;
        }
    }

    return stream.str();
}

std::string StringHelper::replace(const std::string &s, const std::string& from, const std::string& to)
{
    size_t start_pos = s.find(from);

    if(start_pos == std::string::npos)
    {
        return s;
    }

    std::string new_string = s;
    new_string.replace(start_pos, from.length(), to);

    return new_string;
}

bool StringHelper::contains(const std::string& s, const std::string& substring)
{
    std::size_t found = s.find(substring);
    return (found != std::string::npos);
}

std::string StringHelper::toLower(const std::string& s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string StringHelper::toUpper(const std::string& s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

int StringHelper::stringToInt(const std::string& s)
{
    if(s == "")
    {
        return 0;
    }

    std::stringstream convert(trim(s));

    int result;
    if(convert >> result)
    {
        return result;
    }

    return 0;
}

int StringHelper::stringToInt(char c)
{
	switch (c)
	{
	case '0':
		return 0;

	case '1':
		return 1;

	case '2':
		return 2;

	case '3':
		return 3;

	case '4':
		return 4;

	case '5':
		return 5;

	case '6':
		return 6;

	case '7':
		return 7;

	case '8':
		return 8;

	case '9':
		return 9;

	default:
		return 0;
	}
}

std::string StringHelper::boolToString(bool value)
{
    if(value)
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

std::string StringHelper::intToString(int value)
{
    std::stringstream s;

    s << value;

    return s.str();
}

int StringHelper::hexStringToInt(const std::string& s)
{
    if(s == "")
    {
        return 0;
    }

    std::stringstream convert;
    
    convert << std::hex << s;
    
    int result;
    if(convert >> result)
    {
        return result;
    }
    
    return 0;
}

double StringHelper::stringToDouble(const std::string& s)
{
    if(s == "")
    {
        return 0.0;
    }

    std::stringstream convert(trim(s));

    double result;
    if(convert >> result)
    {
        return result;
    }

    return 0.0;
}

std::string StringHelper::doubleToString(double value)
{
    std::stringstream s;

    s << std::fixed << std::setprecision(2);

    s << value;

    return s.str();
}

float StringHelper::stringToFloat(const std::string& s)
{
    if(s == "")
    {
        return 0.0f;
    }

    std::stringstream convert(trim(s));

    float result;
    if(convert >> result)
    {
        return result;
    }

    return 0.0f;
}

std::string StringHelper::floatToString(float value)
{
    std::stringstream s;

    s << std::fixed << std::setprecision(2);

    s << value;

    return s.str();
}

bool StringHelper::stringToBool(const std::string& s)
{
    if(s == "true" || s == "True" || s == "1")
    {
        return true;
    }

    return false;
}

bool StringHelper::hexStringToColorFloat(const std::string& color_string, float &r, float &g, float &b)
{
    int r_i, g_i, b_i;
    if(!hexStringToColor(color_string, r_i, g_i, b_i))
    {
        return false;
    }

    r = static_cast<float>(r_i) / 255.0f;
    g = static_cast<float>(g_i) / 255.0f;
    b = static_cast<float>(b_i) / 255.0f;

    return true;
}

bool StringHelper::hexStringToColor(const std::string& color_string, int &r, int &g, int &b)
{
    std::string s = trim(color_string, '#');

    if(s.size() < 6)
    {
        return false;
    }

    r = hexCharToInt(s[0]) * 16 + hexCharToInt(s[1]);
    g = hexCharToInt(s[2]) * 16 + hexCharToInt(s[3]);
    b = hexCharToInt(s[4]) * 16 + hexCharToInt(s[5]);

    return true;
}

bool StringHelper::hexStringToColor(const std::string& color_string, QColor &color)
{
	int r, g, b;

	if (!hexStringToColor(color_string, r, g, b))
	{
		return false;
	}

	color.setRed(r);
	color.setGreen(g);
	color.setBlue(b);

	return true;
}


int StringHelper::hexCharToInt(char c)
{
    switch(c)
    {
    case '0':
        return 0;

    case '1':
        return 1;

    case '2':
        return 2;

    case '3':
        return 3;

    case '4':
        return 4;

    case '5':
        return 5;

    case '6':
        return 6;

    case '7':
        return 7;

    case '8':
        return 8;

    case '9':
        return 9;

    case 'a':
    case 'A':
        return 10;

    case 'b':
    case 'B':
        return 11;

    case 'c':
    case 'C':
        return 12;

    case 'd':
    case 'D':
        return 13;

    case 'e':
    case 'E':
        return 14;

    case 'f':
    case 'F':
        return 15;
    }

    return 0;
}

std::string StringHelper::switchDirSeperatorsToMac(const std::string& s)
{
    std::string path = s;
    for(unsigned int i = 0; i != path.size(); ++i)
    {
        if(path[i] == '\\')
        {
            path[i] = '/';
        }
    }

    return path;
}

std::string StringHelper::toTimeString(double time)
{
	return toTimeString(static_cast<int>(time + 0.5));
}

std::string StringHelper::toTimeString(int time)
{
	if (time < 0)
	{
		time = 0;
	}

	const int minutes = time / 60;
	const int seconds = time % 60;

	std::string minutes_string = StringHelper::intToString(minutes);
	if (minutes < 10)
	{
		minutes_string = "0" + minutes_string;
	}

	std::string time_string = minutes_string + ":";
	if (seconds < 10)
	{
		time_string += "0";
	}

	time_string += StringHelper::intToString(seconds);

	return time_string;
}