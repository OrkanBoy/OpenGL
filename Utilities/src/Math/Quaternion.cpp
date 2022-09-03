#include "Quaternion.hpp"
#include "../Miscellaneous/ExtGLM.hpp"

namespace Math
{
	Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Quaternion::Quaternion(glm::vec3 vec3, float theta)
	{
		vec3 *= sin(theta);
		x = vec3.x;
		y = vec3.y;
		z = vec3.z;
		w = cos(theta);
	}

	template<glm::length_t n, typename T>
	Quaternion::Quaternion(glm::vec<n, T> vec) 
	{
		for (int i = 0; i < 4; i++)
		{
			if (i < n)
				operator[](i) = vec[i];
			else
				operator[](i) = 0.0f;
		}
	}

	Quaternion::Quaternion(float real) : Quaternion(0.0f, 0.0f, 0.0f, real) {}

	float& Quaternion::operator[](int index) 
	{
		assert(index >= 0 && index <= 3);
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		}
	}



	Quaternion Quaternion::operator+(Quaternion other) { return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w); }
	Quaternion Quaternion::operator+(float f) { return Quaternion(x, y, z, w + f); }


	Quaternion Quaternion::operator-(Quaternion other) { return *this + -other; }
	Quaternion Quaternion::operator-(float f) { return Quaternion(x, y, z, w - f); }
	Quaternion Quaternion::operator-() { return Quaternion(-x, -y, -z, -w); }



	Quaternion Quaternion::operator*(Quaternion other) 
	{
		return Quaternion
		(
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y - x * other.z + y * other.w + z * other.x,
			w * other.z + x * other.y - y * other.x + z * other.w,
			w * other.w - x * other.x - y * other.y - z * other.z
		);
	}
	Quaternion Quaternion::operator*(float f) { return Quaternion(x * f, y * f, z * f, w * f); }



	Quaternion Quaternion::operator/(Quaternion other) { return *this * other.Inverse(); }
	Quaternion Quaternion::operator/(float f) { return Quaternion(x / f, y / f, z / f, w / f); }



	float Quaternion::Length() { return sqrt(w * w + x * x + y * y + z * z); }

	Quaternion Quaternion::Conjugate() { return Quaternion(-x, -y, -z, w); }

	Quaternion Quaternion::Inverse() { return Conjugate() / (w * w + x * x + y * y + z * z); };

	Quaternion Quaternion::Normalized() { return *this / Length(); }



	glm::vec3 Quaternion::Rotate(glm::vec3 v) 
	{
		float theta = acosf(w/Length());
		Quaternion q = Quaternion(glm::vec3(x, y, z), theta/2.0f);
		return (glm::vec3)(q * (Quaternion)v * q.Conjugate());
	}
	glm::vec3 Quaternion::Rotate(glm::vec3 v, glm::vec3 axis, float theta)
	{
		Quaternion q = Quaternion(glm::normalize(axis), theta / 2.0f);
		return (glm::vec3)(q * (Quaternion)v * q.Conjugate());
	}


	Quaternion::operator std::string()
	{
		std::stringstream ss;

		for (int i = 0; i < 4; i++) 
		{
			float& comp = operator[](i);
			if (comp == -0.0f)
				comp = 0.0f;
			if (comp > 0.0f)
				ss << " ";
			ss << truncate(std::to_string(comp), maxEntrySize + (comp < 0.0f ? 1 : 0));
			if (i < 3)
				ss << "ijk"[i] << " + ";
		}
		return ss.str();
	}

	Quaternion::operator glm::vec3() { return glm::vec3(x, y, z); }

	Quaternion::operator glm::mat4()
	{
		return x * Mati + y * Matj + z * Matk + w * glm::mat4(1.0f);
	}

	std::ostream& operator<<(std::ostream& stream, Quaternion q)
	{
		stream << (std::string)q;
		return stream;
	}

	float Quaternion::GetTheta() { return acosf(w / Length()); }

	glm::vec3 Quaternion::GetDir() { return glm::normalize(glm::vec3(x, y, z)); }

	Quaternion expq(Quaternion q) 
	{
		float imaginaryRadius = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z);
		if (imaginaryRadius == 0.0f)
			return (Quaternion)expf(q.w);
		return (Quaternion(q.x, q.y, q.z, 0.0f)/imaginaryRadius * sinf(imaginaryRadius) + cosf(imaginaryRadius)) * expf(q.w);
	}

	Quaternion logq(Quaternion q)
	{
		if (q.x == 0.0f && q.y == 0.0f && q.z == 0.0f)
			return (Quaternion)logf(q.w);
		float r = q.Length();
		float theta = acosf(q.w/r);
		return (Quaternion)q.GetDir() * theta + logf(r);
	}

	Quaternion powq(Quaternion q, Quaternion exponent)
	{
		return expq(logq(q) * exponent);
	}

	Quaternion logq(Quaternion q, Quaternion base)
	{
		return logq(q) / logq(base);
	}

	Quaternion sinq(Quaternion q) 
	{
		Quaternion unitImaginaryComp = (Quaternion)q.GetDir();
		return (expq(unitImaginaryComp * q) - expq(-unitImaginaryComp * q))/ unitImaginaryComp * 0.5f;
	}

	Quaternion cosq(Quaternion q) 
	{
		Quaternion unitImaginaryComp = (Quaternion)q.GetDir();
		return (expq(unitImaginaryComp * q) + expq(unitImaginaryComp * q)) / 0.5f;
	}

	Quaternion tanq(Quaternion q) { return sinq(q) / cosq(q); }
}