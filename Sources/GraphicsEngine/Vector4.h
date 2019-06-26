#pragma once


class Vector4
{
public:
	//double x, y, z, w;
	union {
		struct {
			double x, y, z, w;
		};
		double v[4];
	};

public:

	Vector4()
	: x(0), y(0), z(0), w(0)
	{

	}

	Vector4(double x, double y, double z, double w)
	: x(x), y(y), z(z), w(w)
	{

	}
	
	Vector4(const Vector3 & vec, double w)
	: x(vec.x), y(vec.y), z(vec.z), w(w)
	{

	}

	Vector4(const Vector4 & vec)
	: x(vec.x), y(vec.y), z(vec.z), w(vec.w)
	{

	}

	const Vector3 ToVector3() const
	{
		Vector3 result = Vector3(x, y, z);

		return result;
	}

	const Vector4 & operator += (const Vector4 & vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		this->w += vec.w;

		return *this;
	}

	const Vector4 & operator -= (const Vector4 & vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		this->w -= vec.w;

		return *this;
	}

	const Vector4 & operator *= (const double k)
	{
		this->x *= k;
		this->y *= k;
		this->z *= k;
		this->w *= k;

		return *this;
	}

	const Vector4 & operator /= (const double k)
	{
		const double k1 = 1.0 / k;

		this->x *= k1;
		this->y *= k1;
		this->z *= k1;
		this->w *= k1;

		return *this;
	}

	const Vector4 operator + (const Vector4 & vec) const
	{
		Vector4 result(*this);

		result += vec;

		return result;
	}

	const Vector4 operator - (const Vector4 & vec) const
	{
		Vector4 result(*this);

		result -= vec;

		return result;
	}

	const Vector4 operator * (const double k) const
	{
		Vector4 result(*this);

		result *= k;

		return result;
	}

    static double Dot(const Vector4 & a, const Vector4 & b)
	{
		double result = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;

		return result;
	}

	void Normalize()
	{
		double length = sqrt(x*x + y*y + z*z + w*w);

		*this *= (1.0 / length);
	}

	double Norma()
	{
		double length = sqrt(x*x + y*y + z*z + w*w);

		return length;
	}

	static Vector4 Zero()
	{
		return Vector4();
	}
};
