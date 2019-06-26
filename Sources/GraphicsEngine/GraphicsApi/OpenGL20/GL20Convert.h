#pragma once
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/Matrix4x4.h"


class GL20Convert
{
public:
	
	static void ToGL20Vector4(const Vector4 & from, GLfloat * to)
	{
		for (int i = 0; i < 4; ++i)
		{
			to[i] = static_cast<GLfloat>( from.v[i] );
		}
	}

	static void ToGL20Matrix4x4(const Matrix4x4 & from, GLfloat * to)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				to[4 * i + j] = static_cast<GLfloat>( from.m[i][j] );
			}
		}
	}
};
