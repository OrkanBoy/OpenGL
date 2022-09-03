#include "String.hpp"

std::string operator*(std::string str, int c)
{
    std::string resStr = "";
    for (int i = 0; i < c; i++)
        resStr += str;
    return resStr;
}

std::string truncate(std::string str, int width)
{
    if (width > str.length())
        return str + std::string(" ") * (width - str.length());
    return str.substr(0, width);
}

std::string GetWord(const std::string& source, const unsigned int& index)
{
    int charIndex = 0;
    for (int wordIndex = 0; wordIndex < index; wordIndex++)
    {
        while (source[charIndex] == ' ' || source[charIndex] == '\n')
        {
            charIndex++;
            if (charIndex >= source.length())
                return "";
        }
        while (source[charIndex] != ' ' && source[charIndex] != '\n')
        {
            charIndex++;
            if (charIndex >= source.length())
                return "";
        }
    }

    while (source[charIndex] == ' ' || source[charIndex] == '\n')
    {
        charIndex++;
        if (charIndex >= source.length())
            return "";
    }

    int count = 0;
    while (!(charIndex >= source.length() || source[charIndex] == ' ' || source[charIndex] == '\n'))
    {
        charIndex++;
        count++;
    }
    return source.substr(charIndex - count, count);
}