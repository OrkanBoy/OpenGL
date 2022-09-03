#pragma once

#include "GLObject.hpp"

namespace glo
{
	class Texture : public GLObject
	{
	private:
		unsigned char* data = nullptr;
		int width = 0, height = 0, bpp = 2;

	public:
		unsigned int unit;

		Texture(unsigned int unit, const std::string& path);

		~Texture();

		void Bind() const override;

		void Unbind() const;

		void Parameteri(GLenum pname, int param);

		void Parameterf(GLenum pname, float param);

		void Parametersi(GLenum pname, int* params);

		void Parametersf(GLenum pname, float* params);
	};

}
