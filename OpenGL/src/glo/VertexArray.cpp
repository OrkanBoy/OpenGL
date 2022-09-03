#include "VertexArray.hpp"

namespace glo
{
	VertexArray::VertexArray(unsigned int totalComponents) : stride(totalComponents * sizeof(float))
	{
		GLCall(glGenVertexArrays(1, &id));
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &id));
	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(id));
	}

	void VertexArray::Unbind()
	{
		GLCall(glBindVertexArray(0));
	}

	void VertexArray::Push(unsigned int components, bool normalised)
	{
		GLCall(glVertexAttribPointer(count, components, GL_FLOAT, normalised ? GL_TRUE : GL_FALSE, stride, (void*)offset));
		Enable(count++);
		offset += components * sizeof(float);
	}

	void VertexArray::Enable(unsigned int index)
	{
		if (index >= count)
			Log("Cannot enable index if its bigger or equal to the count of attributes");
		GLCall(glEnableVertexAttribArray(index));
	}

	void VertexArray::Disable(unsigned int index)
	{
		GLCall(glDisableVertexAttribArray(index));
	}

	unsigned int VertexArray::GetStride() const { return stride; }
}
