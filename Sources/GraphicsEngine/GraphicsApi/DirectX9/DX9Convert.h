#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9.h"
#include "GraphicsEngine/Vector3.h"
#include "GraphicsEngine/Vector4.h"
#include "GraphicsEngine/Matrix4x4.h"


class DX9Convert
{
public:
	
	static D3DXVECTOR3 ToDX9Vector3(const Vector3 & v)
	{
		return D3DXVECTOR3((FLOAT) v.x, (FLOAT) v.y, (FLOAT) v.z);
	}

	static D3DXVECTOR4 ToDX9Vector4(const Vector4 & v)
	{
		D3DXVECTOR4 vec4 = D3DXVECTOR4((FLOAT) v.x, (FLOAT) v.y, (FLOAT) v.z, (FLOAT) v.w);
		return vec4;
	}

	static D3DXMATRIX ToDX9Matrix4x4(const Matrix4x4 & mat)
	{
		D3DXMATRIX result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] = (FLOAT) mat.m[i][j];
			}
		}

		return result;
	}
};

#endif
