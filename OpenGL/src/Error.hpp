#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define Log(x) std::cout << x << '\n'
#define Assert(condition) if(!(condition)) __debugbreak();  
#define GLCall(func) GLClearErrors();\
    func;\
    Assert(GLCheckError(#func, __FILE__, __LINE__))

void GLClearErrors();

bool GLCheckError(const char* function, const char* file, int line);