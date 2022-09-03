#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <map>
#include <functional>
#include <string>

#include "Error.hpp"
#include "GLObject.hpp"

namespace glo
{
	static std::map<std::string, int> NameToEnum{
	{"vertex", GL_VERTEX_SHADER},
	{"fragment", GL_FRAGMENT_SHADER},
	{"geometry", GL_GEOMETRY_SHADER}
	};

	class Program : public GLObject
	{
	private:
		std::map<std::string, std::string> shaders;

	public:
		std::string& GetShaderScript(const std::string& name);

		int GetUniformLocation(std::string name);

		void SetUniform1i(std::string name, int value);

		void SetUniform1f(std::string name, float value);

		void SetUniform2f(std::string name, float v0, float v1);

		void SetUniform3f(std::string name, float v0, float v1, float v2);

		void SetUniform4f(std::string name, float v0, float v1, float v2, float v3);

		void SetUniformMat4f(std::string name, glm::mat4 mat4);

		template<int n, typename T>
		void SetUniformVec(std::string name, glm::vec<n, T> vec)
		{
			int uniformLocation = GetUniformLocation(name);
			switch (n)
			{
			case 1:
				GLCall(glUniform1f(uniformLocation, vec[0])); break;
			case 2:
				GLCall(glUniform2f(uniformLocation, vec[0], vec[1])); break;
			case 3:
				GLCall(glUniform3f(uniformLocation, vec[0], vec[1], vec[2])); break;
			case 4:
				GLCall(glUniform4f(uniformLocation, vec[0], vec[1], vec[2], vec[3])); break;
			}
		}

		template<int n, int m, typename T>
		void SetUniformMat(std::string name, glm::mat<n, m, T> mat)
		{
			assert(n >= 2 && n <= 4 && m >= 2 && m <= 4);
			int uniformLocation = GetUniformLocation(name);
			auto data = &mat[0][0];
			switch (n)
			{
			case 2:
				switch (m)
				{
				case 2:
					GLCall(glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, data)); break;
				case 3:
					GLCall(glUniformMatrix2x3fv(uniformLocation, 1, GL_FALSE, data)); break;
				case 4:
					GLCall(glUniformMatrix2x4fv(uniformLocation, 1, GL_FALSE, data)); break;
				}
			case 3:
				switch (m)
				{
				case 2:
					GLCall(glUniformMatrix3x2fv(uniformLocation, 1, GL_FALSE, data)); break;
				case 3:
					GLCall(glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, data)); break;
				case 4:
					GLCall(glUniformMatrix3x4fv(uniformLocation, 1, GL_FALSE, data)); break;
				}
			case 4:
				switch (m)
				{
				case 2:
					GLCall(glUniformMatrix4x2fv(uniformLocation, 1, GL_FALSE, data)); break;
				case 3:
					GLCall(glUniformMatrix4x3fv(uniformLocation, 1, GL_FALSE, data)); break;
				case 4:
					GLCall(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, data)); break;
				}
			}
		}

		Program(const std::string& filepath);

		~Program() override;

		void Bind() const override;

		static void Unbind();
	};
	unsigned int CompileShader(unsigned int type, const std::string& source);

	unsigned int CreateShaders(std::map<std::string, std::string>& shaders);

	std::map<std::string, std::string> ParseShaders(const std::string& filepath);
	; }