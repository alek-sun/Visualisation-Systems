#pragma once
#include <math.h>
#include "GraphicsEngine/Math.h"


class Vector3
{
public:
	double x, y, z;

public:

	Vector3()
	: x(0), y(0), z(0)
	{

	}

	Vector3(double x, double y, double z)
	: x(x), y(y), z(z)
	{

	}

	Vector3(const Vector3 & vec)
	: x(vec.x), y(vec.y), z(vec.z)
	{

	}

	Vector3 operator - () const
	{
		return Vector3(-x, -y, -z);
	}

	const Vector3 & operator += (const Vector3 & vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;

		return *this;
	}

	const Vector3 & operator -= (const Vector3 & vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;

		return *this;
	}

	const Vector3 & operator *= (const double k)
	{
		this->x *= k;
		this->y *= k;
		this->z *= k;

		return *this;
	}

	double Length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	Vector3 & Normalize()
	{
		*this *= (1.0 / this->Length());

		return *this;
	}	

    static double Dot(const Vector3 & a, const Vector3 & b)
	{
        return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	static Vector3 Cross(const Vector3 & a, const Vector3 & b)
	{
		return	Vector3
				(
					  a.y * b.z - a.z * b.y,
					-(a.x * b.z - a.z * b.x),
					  a.x * b.y - a.y * b.x
				);
	}

	/**
	* @brief Clamps vector coordinates by interval [0,1].
	*/
	static Vector3 Clamp01(const Vector3 & a)
	{
		return	Vector3
				(
					Math::Clamp(a.x, 0.0, 1.0),
					Math::Clamp(a.y, 0.0, 1.0),
					Math::Clamp(a.z, 0.0, 1.0)
				);
	}

	static Vector3 Zero()
	{
		return Vector3(0, 0, 0);
	}
};

Vector3 operator + (const Vector3 & vec1, const Vector3 & vec2);
Vector3 operator - (const Vector3 & vec1, const Vector3 & vec2);
Vector3 operator * (const Vector3 & vec, const double k);
Vector3 operator * (const double k, const Vector3 & vec);
