#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Math
{
	float const pi = 3.1415927f;
	float const degToRad = 2 * pi / 360.0f;
	float const radToDeg = 1 / degToRad;

	void bound(float& value, float lb, float ub);

	const glm::vec3 unitX = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 unitY = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 unitZ = glm::vec3(0.0f, 0.0f, 1.0f);
}