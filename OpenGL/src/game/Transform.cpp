#include "Transform.hpp"

namespace glm
{
	vec3 proj(vec3 v, vec3 onto)
	{
		vec3 n = normalize(onto);
		return dot(v, n) * n;
	}

	vec3 perp(vec3 v, vec3 onto)
	{
		return v - proj(v, onto);
	}

	float angle(vec3 u, vec3 v)
	{
		return acos(dot(u, v) / (u.length() * v.length()));
	}
}

namespace game
{
	Transform::Transform(vec3 position, vec3 scale) : position(position), scale(scale) {}

	void Transform::SetFront(vec3 front) 
	{
		this->front = normalize(front);
		right = normalize(perp(right, front));
		up = normalize(perp(up, front));
	};
	void Transform::SetRight(vec3 right) 
	{
		this->right = normalize(right);
		front = normalize(perp(front, right));
		up = normalize(perp(up, right));
	};
	void Transform::SetUp(vec3 up)
	{
		this->up = normalize(up);
		front = normalize(perp(front, up));
		right = normalize(perp(right, up));
	};
	void Transform::SetAngle(vec3 axis, float angle)
	{
		front = Math::Quaternion::Rotate(front, axis, glm::radians(angle));
		right = Math::Quaternion::Rotate(right, axis, glm::radians(angle));
		up = cross(front, right);
	}

	vec3 Transform::GetFront() { return front; }
	vec3 Transform::GetRight() { return right; }
	vec3 Transform::GetUp() { return up; }
	float Transform::GetAngle(vec3 axis, vec3 ref)
	{
		vec3 n = normalize(axis);
		if (ref == vec3(0.0f))
			ref = front;
		return glm::angle(perp(n, ref), perp(n, right + up));
	}

	mat4 Transform::GetModel() 
	{
		glm::mat4 model = glm::scale(glm::mat4(1.0f), scale);
		model = glm::rotate(model, glm::angle(front, glm::vec3(0.0f, 0.0f, -1.0f)), cross(front, glm::vec3(0.0f, 0.0f, -1.0f)));
		model = glm::translate(model, position);
		return model;
	}
}