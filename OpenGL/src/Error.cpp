#include "Error.hpp"

void GLClearErrors()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLCheckError(const char* function, const char* file, int line)
{
    if (GLenum error = glGetError())
    {
        Log("[OpenGL Error]" << "(" << error << ")" << "Error at: \n function: " << function << "\n file: " << file << "\n line: " << line);
        return false;
    }
    return true;
}