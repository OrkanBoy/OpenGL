#pragma once

#include "Error.hpp"
#include "GLObject.hpp"

namespace glo
{
	class Buffer : public GLObject
	{
	public:
		unsigned int target;

		Buffer(const GLenum& target);

		~Buffer() override;

		void Fill(unsigned int size, const void* data = 0, const GLenum& usage = GL_STATIC_DRAW);

		void Bind() const override;

		static void Unbind(const GLenum& target);
	};
}


