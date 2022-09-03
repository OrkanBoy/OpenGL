#pragma once

#include <map>

#include "GLObject.hpp"

namespace glo
{
	class VertexArray : public GLObject
	{
	private:
		unsigned int stride;

		unsigned int offset = 0;

	public:
		unsigned int count = 0;

		VertexArray(unsigned int totalComponents);

		~VertexArray() override;

		void Bind() const override;

		static void Unbind();

		void Push(unsigned int components, bool normalised = false);

		void Enable(unsigned int index);

		void Disable(unsigned int index);

		unsigned int GetStride() const;

		unsigned int GetOffset() const;
	};
}