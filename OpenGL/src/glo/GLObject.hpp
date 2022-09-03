#pragma once

#include "../Error.hpp"

namespace glo
{
	class GLObject
	{
	public:
		unsigned int id;

		virtual ~GLObject() = 0;

		virtual void Bind() const = 0;
	};
}
