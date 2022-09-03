#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <sstream>

namespace Math
{


	struct Quaternion
	{
		float x, y, z, w;
		Quaternion(float x, float y, float z, float w);
		Quaternion(glm::vec3 vec3, float theta);
		template<glm::length_t n, typename T>
		explicit Quaternion(glm::vec<n, T> vec);
		explicit Quaternion(float f);

		float& operator[](int index);

		Quaternion operator+(Quaternion other);
		Quaternion operator+(float f);

		Quaternion operator-(Quaternion other);
		Quaternion operator-(float f);
		Quaternion operator-();

		Quaternion operator*(Quaternion other);
		Quaternion operator*(float f);

		Quaternion operator/(Quaternion other);
		Quaternion operator/(float f);

		float Length();

		Quaternion Inverse();
		
		Quaternion Conjugate();

		Quaternion Normalized();

		glm::vec3 Rotate(glm::vec3 v);
		static glm::vec3 Rotate(glm::vec3 v, glm::vec3 axis, float theta);

		explicit operator std::string();

		explicit operator glm::vec3();

		explicit operator glm::mat4();

		float GetTheta();

		glm::vec3 GetDir();

	};

	std::ostream& operator<<(std::ostream& stream, Quaternion q);

	const Quaternion i = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	const Quaternion j = Quaternion(0.0f, 1.0f, 0.0f, 0.0f);
	const Quaternion k = Quaternion(0.0f, 0.0f, 1.0f, 0.0f);


	//remember, column major ordering, so looks transposed than how you actually write on pen and paper
	const glm::mat4 Mati = glm::mat4
	{
		0.0f, 0.0f, 0.0f, -1.0f, 
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 0.0f
	};
	const glm::mat4 Matj = glm::mat4
	{
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f
	};
	const glm::mat4 Matk = glm::mat4
	{
		0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, 1.0f, 0.0f
	};
	Quaternion expq(Quaternion q);

	Quaternion logq(Quaternion q);

	Quaternion powq(Quaternion q, Quaternion exponent);

	Quaternion logq(Quaternion q, Quaternion base);

	Quaternion sinq(Quaternion q);

	Quaternion cosq(Quaternion q);
	
	Quaternion tanq(Quaternion q);
}

