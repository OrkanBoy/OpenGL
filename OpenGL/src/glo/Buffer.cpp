#include "Buffer.hpp"

namespace glo
{
	Buffer::Buffer(const GLenum& target) : target(target)
	{
		GLCall(glGenBuffers(1, &id));
	}

	Buffer::~Buffer()
	{
		GLCall(glDeleteBuffers(1, &id));
	}

	void Buffer::Fill(unsigned int size, const void* data, const GLenum& usage)
	{
		Bind();
		GLCall(glBufferData(target, size, data, usage));
	}

	void Buffer::Bind() const
	{
		GLCall(glBindBuffer(target, id));
	}

	void Buffer::Unbind(const GLenum& target)
	{
		GLCall(glBindBuffer(target, 0));
	}
}
