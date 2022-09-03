#include <fstream>
#include <sstream>

#include "Miscellaneous/String.hpp"
#include "Program.hpp"

namespace glo
{

    Program::Program(const std::string& filepath)
    {
        shaders = ParseShaders(filepath);
        id = CreateShaders(shaders);
    };

    Program::~Program()
    {
        GLCall(glDeleteProgram(id));
    }

    std::string& Program::GetShaderScript(const std::string& name)
    {
        return shaders[name];
    }

    int Program::GetUniformLocation(std::string name)
    {
        GLCall(return glGetUniformLocation(id, name.c_str()));
    }

    void Program::SetUniform1i(std::string name, int value)
    {
        GLCall(glUniform1i(GetUniformLocation(name), value));
    }

    void Program::SetUniform1f(std::string name, float value)
    {
        GLCall(glUniform1f(GetUniformLocation(name), value))
    }

    void Program::SetUniform2f(std::string name, float v0, float v1)
    {
        GLCall(glUniform2f(GetUniformLocation(name), v0, v1));
    }

    void Program::SetUniform3f(std::string name, float v0, float v1, float v2)
    {
        GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
    }

    void Program::SetUniform4f(std::string name, float v0, float v1, float v2, float v3)
    {
        GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
    }

    void Program::SetUniformMat4f(std::string name, glm::mat4 mat4)
    {
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat4[0][0]));
    }

    void Program::Bind() const
    {
        GLCall(glUseProgram(id));
    }

    void Program::Unbind()
    {
        GLCall(glUseProgram(0));
    }

    unsigned int CompileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        GLCall(glShaderSource(id, 1, &src, nullptr));
        GLCall(glCompileShader(id));

        int result;
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE)
        {
            int length;
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* message = (char*)_malloca(length * sizeof(char));
            GLCall(glGetShaderInfoLog(id, length, &length, message));
            std::cout << message << std::endl;
            GLCall(glDeleteShader(id));
            return 0;
        }

        return id;
    }

    unsigned int CreateShaders(std::map<std::string, std::string>& shaders)
    {
        GLCall(unsigned int program = glCreateProgram());

        unsigned int* shaderIds = new unsigned int[shaders.size()];
        int i = 0;
        for (auto [shaderName, shaderScript] : shaders)
        {
            shaderIds[i] = CompileShader(NameToEnum[shaderName], shaderScript);
            GLCall(glAttachShader(program, shaderIds[i++]));
        }

        GLCall(glLinkProgram(program));
        GLCall(glValidateProgram(program));

        for (auto [shaderName, _] : shaders)
            GLCall(glDeleteShader(shaderIds[--i]));

        return program;
    }

    std::map<std::string, std::string> ParseShaders(const std::string& filepath)
    {
        std::ifstream stream = std::ifstream(filepath);
        std::string curShaderType = "none";

        std::map<std::string, std::string> shaders;
        std::stringstream ss;
        std::string line;
        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                std::string shaderType = GetWord(line, 1);
                if (curShaderType != "none")
                    shaders[curShaderType] = ss.str();
                ss.str("");
                curShaderType = shaderType;
                shaders[shaderType];
            }
            else
                ss << line << '\n';
        }
        shaders[curShaderType] = ss.str();
        return shaders;
    }
}


