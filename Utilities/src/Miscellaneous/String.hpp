#pragma once

#include <iostream>

std::string operator*(std::string str, int c);

std::string truncate(std::string str, int width);

std::string GetWord(const std::string& source, const unsigned int& index);