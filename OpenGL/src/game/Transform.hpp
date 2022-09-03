#pragma once

#include "glm/glm.hpp"
#include "Math/Quaternion.hpp"

using glm::vec3, glm::mat4;

namespace game
{

	class Transform
	{
	private:
		vec3 front = vec3(0.0f, 0.0f, -1.0f),
			right = vec3(1.0f, 0.0f, 0.0f),
			up = vec3(0.0, 1.0f, 0.0f);

	public:
		Transform(vec3 position, vec3 scale);

		vec3 position = vec3(0.0f);
		vec3 scale = vec3(1.0f);
		
		vec3 GetFront();
		vec3 GetRight();
		vec3 GetUp();
		float GetAngle(vec3 axis, vec3 ref = vec3(0.0f));

		void SetFront(vec3 front);
		void SetRight(vec3 right);
		void SetUp(vec3 up);
		void SetAngle(vec3 axis, float angle);
		
		mat4 GetModel();
	};
}