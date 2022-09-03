#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "String.hpp"
#include <iostream>
#include <sstream>

const int maxEntrySize = 5;
const static int spacing = 2;

template<glm::length_t toN, glm::length_t fromN, typename T>
glm::vec<toN, T> AsVector(glm::mat<fromN, fromN, T> m)
{
    glm::vec<toN, T> v = glm::vec<toN, T>();
    for (int i = 0; i < fmin(toN, fromN); i++)
        v[i] = m[i][i]; 
    return v;
}

template<glm::length_t toN, glm::length_t fromN, typename T>
glm::mat<toN, toN, T> AsMatrix(glm::vec<fromN, T> v)
{
    glm::mat<toN, toN, T> m = glm::mat<toN, toN, T>(0.0f);
    for (int i = 0; i < fmin(toN, fromN); i++)
        m[i][i] = v[i];
    return m;
}

template<int rows, typename T>
std::ostream& operator<<(std::ostream& stream, glm::vec<rows, T> vec)
{
    std::stringstream ss;
    ss << "(";
    for (int i = 0; i < rows; i++)
    {
        float& entry = vec[i];
        if (entry == -0.0f)
            entry = 0.0f;
        ss << truncate(std::to_string(entry), maxEntrySize + (entry < 0.0f ? 1 : 0));
        if (i < rows - 1)
            ss << "," << std::string(" ") * (spacing - 1);
    }
    ss << ")";
    stream << ss.str();
    return stream;
}

template<int columns, int rows, typename T>
std::ostream& operator<<(std::ostream& stream, glm::mat<columns, rows, T> mat)
{
    std::stringstream ss;
    for (int i = 0; i < rows; i++)
    {
        ss << "|";
        for (int j = 0; j < columns; j++)
        {
            float entry = mat[j][i];
            if (entry == -0.0f)
                entry = 0.0f;
            if (entry >= 0.0f)
                ss << " ";
            ss << truncate(std::to_string(entry), maxEntrySize + (entry < 0.0f ? 1 : 0));
            if (j < columns - 1)
                ss << std::string(" ") * spacing;
        }
        ss << " |\n";
    }
    stream << ss.str();
    return stream;
}

