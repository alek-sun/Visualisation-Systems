#include "GraphicsEngine/Vector3.h"


Vector3 operator + (const Vector3 & vec1, const Vector3 & vec2)
{
	Vector3 result(vec1);

	result += vec2;

	return result;
}

Vector3 operator - (const Vector3 & vec1, const Vector3 & vec2)
{
	Vector3 result(vec1);

	result -= vec2;

	return result;
}

Vector3 operator * (const Vector3 & vec, const double k)
{
	Vector3 result(vec);

	result *= k;

	return result;
}

Vector3 operator * (const double k, const Vector3 & vec)
{
	Vector3 result(vec * k);

	return result;
}
