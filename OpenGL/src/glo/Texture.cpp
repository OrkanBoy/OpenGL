#include "other/stb/stb_image.h"

#include "Texture.hpp"

namespace glo
{
	Texture::Texture(unsigned int unit, const std::string& path) : unit(unit)
	{
		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(path.c_str(), &width, &height, &bpp, 4);

		GLCall(glGenTextures(1, &id));
		Bind();

		Parameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		Parameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Parameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
		Parameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		Unbind(); 

		if (data)
			stbi_image_free(data);
		else
			Log("Failed to load " + path);
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &id));
	}

	void Texture::Bind() const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + unit));
		GLCall(glBindTexture(GL_TEXTURE_2D, id));
	}

	void Texture::Unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void Texture::Parameteri(GLenum pname, int param)
	{
		GLCall(glTexParameteri(GL_TEXTURE_2D, pname, param));
	}

	void Texture::Parameterf(GLenum pname, float param)
	{
		GLCall(glTexParameterf(GL_TEXTURE_2D, pname, param));
	}

	void Texture::Parametersi(GLenum pname, int* params)
	{
		GLCall(glTexParameteriv(GL_TEXTURE_2D, pname, params));
	}

	void Texture::Parametersf(GLenum pname, float* params)
	{
		GLCall(glTexParameterfv(GL_TEXTURE_2D, pname, params));
	}
}



