#pragma once
#include <math.h>
#include "GraphicsEngine/MathConstants.h"
#include "GraphicsEngine/Vector3.h"
#include "GraphicsEngine/Vector4.h"


struct Matrix4x4
{
	union {
		struct {
			double m11, m12, m13, m14;
			double m21, m22, m23, m24;
			double m31, m32, m33, m34;
			double m41, m42, m43, m44;
		};
		double m[4][4];
	};
	
	Matrix4x4 & operator = (const Matrix4x4 & that)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] = that.m[i][j];
			}
		}

		return (*this);
	}

	Matrix4x4 operator * (const Matrix4x4 & that) const
	{
		Matrix4x4 result;

		for (int i = 0; i < 4; i++)
		{
			for (int i2 = 0; i2 < 4; i2++)
			{
				double total = 0.0f;
				for (int i3 = 0; i3 < 4; i3++)
				{
					total += m[i][i3] * that.m[i3][i2];
				}
				result.m[i][i2] = total;
			}
		}

		return result;
	}

	Vector4 operator * (const Vector4 & vec) const
	{
		Vector4 result = Vector4::Zero();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.v[i] += m[j][i] * vec.v[j];
			}
		}

		return result;
	}

    static Matrix4x4 Identity()
	{
		Matrix4x4 result;
		
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
				{
					result.m[i][j] = 1.0f;
				}
				else
				{
					result.m[i][j] = 0.0f;
				}
			}
		}

		return result;
	}

	
	Matrix4x4 Transpose() const
	{
		Matrix4x4 result;
		
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] = m[j][i];
			}
		}

		return result;
	}

	Matrix4x4 Inverse() const
	{
		//
		// Inversion by Cramer's rule.  Code taken from an Intel publication
		//
		double res[4][4];
		double tmp[12]; /* temp array for pairs */
		double src[16]; /* array of transpose source matrix */
		double det; /* determinant */
		/* transpose matrix */
		for (int i = 0; i < 4; i++)
		{
			src[i + 0 ] = (*this).m[i][0];
			src[i + 4 ] = (*this).m[i][1];
			src[i + 8 ] = (*this).m[i][2];
			src[i + 12] = (*this).m[i][3];
		}
		/* calculate pairs for first 8 elements (cofactors) */
		tmp[0] = src[10] * src[15];
		tmp[1] = src[11] * src[14];
		tmp[2] = src[9]  * src[15];
		tmp[3] = src[11] * src[13];
		tmp[4] = src[9]  * src[14];
		tmp[5] = src[10] * src[13];
		tmp[6] = src[8]  * src[15];
		tmp[7] = src[11] * src[12];
		tmp[8] = src[8]  * src[14];
		tmp[9] = src[10] * src[12];
		tmp[10] = src[8] * src[13];
		tmp[11] = src[9] * src[12];
		/* calculate first 8 elements (cofactors) */
		res[0][0] =  tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
		res[0][0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
		res[0][1] =  tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
		res[0][1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
		res[0][2] =  tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
		res[0][2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
		res[0][3] =  tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
		res[0][3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
		res[1][0] =  tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
		res[1][0] -= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];
		res[1][1] =  tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
		res[1][1] -= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];
		res[1][2] =  tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
		res[1][2] -= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
		res[1][3] =  tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
		res[1][3] -= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];
		/* calculate pairs for second 8 elements (cofactors) */
		tmp[0] = src[2]*src[7];
		tmp[1] = src[3]*src[6];
		tmp[2] = src[1]*src[7];
		tmp[3] = src[3]*src[5];
		tmp[4] = src[1]*src[6];
		tmp[5] = src[2]*src[5];

		tmp[6]  = src[0]*src[7];
		tmp[7]  = src[3]*src[4];
		tmp[8]  = src[0]*src[6];
		tmp[9]  = src[2]*src[4];
		tmp[10] = src[0]*src[5];
		tmp[11] = src[1]*src[4];
		/* calculate second 8 elements (cofactors) */
		res[2][0] =  tmp[0]*src[13]  + tmp[3]*src[14]  + tmp[4]*src[15];
		res[2][0] -= tmp[1]*src[13]  + tmp[2]*src[14]  + tmp[5]*src[15];
		res[2][1] =  tmp[1]*src[12]  + tmp[6]*src[14]  + tmp[9]*src[15];
		res[2][1] -= tmp[0]*src[12]  + tmp[7]*src[14]  + tmp[8]*src[15];
		res[2][2] =  tmp[2]*src[12]  + tmp[7]*src[13]  + tmp[10]*src[15];
		res[2][2] -= tmp[3]*src[12]  + tmp[6]*src[13]  + tmp[11]*src[15];
		res[2][3] =  tmp[5]*src[12]  + tmp[8]*src[13]  + tmp[11]*src[14];
		res[2][3] -= tmp[4]*src[12]  + tmp[9]*src[13]  + tmp[10]*src[14];
		res[3][0] =  tmp[2]*src[10]  + tmp[5]*src[11]  + tmp[1]*src[9];
		res[3][0] -= tmp[4]*src[11]  + tmp[0]*src[9]   + tmp[3]*src[10];
		res[3][1] =  tmp[8]*src[11]  + tmp[0]*src[8]   + tmp[7]*src[10];
		res[3][1] -= tmp[6]*src[10]  + tmp[9]*src[11]  + tmp[1]*src[8];
		res[3][2] =  tmp[6]*src[9]   + tmp[11]*src[11] + tmp[3]*src[8];
		res[3][2] -= tmp[10]*src[11] + tmp[2]*src[8]   + tmp[7]*src[9];
		res[3][3] =  tmp[10]*src[10] + tmp[4]*src[8]   + tmp[9]*src[9];
		res[3][3] -= tmp[8]*src[9]   + tmp[11]*src[10] + tmp[5]*src[8];
		/* calculate determinant */
		det=src[0]*res[0][0]+src[1]*res[0][1]+src[2]*res[0][2]+src[3]*res[0][3];
		/* calculate matrix inverse */
		det = 1.0f / det;

		Matrix4x4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] = res[i][j] * det;
			}
		}

		return result;
	}

	static Matrix4x4 Translation(const Vector3 & position)
	{
		Matrix4x4 result = Matrix4x4::Identity();
		
		result.m[3][0] = position.x;
		result.m[3][1] = position.y;
		result.m[3][2] = position.z;

		return result;
	}

	static Matrix4x4 Rotation(Vector3 eulerAnglesInDegrees)
	{
		return RotationY(eulerAnglesInDegrees.y) * RotationX(eulerAnglesInDegrees.x) * RotationZ(eulerAnglesInDegrees.z);
	}

	static Matrix4x4 RotationX(double xInDegrees)
	{
		double x = xInDegrees * DEG2RAD;
		double CosT = cos(x);
		double SinT = sin(x);

		Matrix4x4 result = Identity();
		
		result.m[1][1] = CosT;
		result.m[1][2] = SinT;
		result.m[2][1] = -SinT;
		result.m[2][2] = CosT;

		return result;
	}

	static Matrix4x4 RotationY(double yInDegrees)
	{
		double y = yInDegrees * DEG2RAD;
		double CosT = cos(y);
		double SinT = sin(y);

		Matrix4x4 result = Identity();
		
		result.m[0][0] = CosT;
		result.m[0][2] = -SinT;
		result.m[2][0] = SinT;
		result.m[2][2] = CosT;

		return result;
	}

	static Matrix4x4 RotationZ(double zInDegrees)
	{
		double z = zInDegrees * DEG2RAD;
		double CosT = cos(z);
		double SinT = sin(z);

		Matrix4x4 result = Identity();

		result.m[0][0] = CosT;
		result.m[0][1] = SinT;
		result.m[1][0] = -SinT;
		result.m[1][1] = CosT;

		return result;
	}

	static Matrix4x4 Scaling(const Vector3 & scale)
	{
		Matrix4x4 result = Matrix4x4::Identity();
		
		result.m[0][0] = scale.x;
		result.m[1][1] = scale.y;
		result.m[2][2] = scale.z;
		
		return result;
	}

	static Matrix4x4 LookAtLH(Vector3 eyePoint, Vector3 lookAtPoint, Vector3 up)
	{
		Vector3 zaxis = (lookAtPoint - eyePoint).Normalize();
		Vector3 xaxis = Vector3::Cross(up, zaxis).Normalize();
		Vector3 yaxis = Vector3::Cross(zaxis, xaxis);

		Matrix4x4 result;

		result.m11 = xaxis.x;
		result.m12 = yaxis.x;
		result.m13 = zaxis.x;
		result.m14 = 0;

		result.m21 = xaxis.y;
		result.m22 = yaxis.y;
		result.m23 = zaxis.y;
		result.m24 = 0;

		result.m31 = xaxis.z;
		result.m32 = yaxis.z;
		result.m33 = zaxis.z;
		result.m34 = 0;

		result.m41 = -Vector3::Dot(xaxis, eyePoint);
		result.m42 = -Vector3::Dot(yaxis, eyePoint);
		result.m43 = -Vector3::Dot(zaxis, eyePoint);
		result.m44 = 1;

		return result;
	}

	static Matrix4x4 PerspectiveFovLH(double fovY, double aspect, double znear, double zfar)
	{
		double yScale = 1.0 / tan(fovY/2 * DEG2RAD);
		double xScale = yScale / aspect;

		Matrix4x4 result;

		result.m11 = xScale;
		result.m12 = 0;
		result.m13 = 0;
		result.m14 = 0;

		result.m21 = 0;
		result.m22 = yScale;
		result.m23 = 0;
		result.m24 = 0;

		result.m31 = 0;
		result.m32 = 0;
		result.m33 = zfar / (zfar - znear);
		result.m34 = 1;

		result.m41 = 0;
		result.m42 = 0;
		result.m43 = - znear * zfar / (zfar - znear);
		result.m44 = 0;

		return result;
	}

	static Matrix4x4 OrhographicLH(double w, double h, double znear, double zfar)
	{
		Matrix4x4 result;

		result.m11 = 2.0 / w;
		result.m12 = 0;
		result.m13 = 0;
		result.m14 = 0;

		result.m21 = 0;
		result.m22 = 2.0 / h;
		result.m23 = 0;
		result.m24 = 0;

		result.m31 = 0;
		result.m32 = 0;
		result.m33 = 1.0 / (zfar - znear);
		result.m34 = 0;

		result.m41 = 0;
		result.m42 = 0;
		result.m43 = - znear / (zfar - znear);
		result.m44 = 1;

		return result;
	}
};
