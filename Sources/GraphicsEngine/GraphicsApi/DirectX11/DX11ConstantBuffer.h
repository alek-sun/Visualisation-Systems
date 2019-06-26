#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11.h"
#include "GraphicsEngine/Matrix4x4.h"
#include <vector>


class DX11ConstantBuffer
{
public:
	void Init(ID3D11Device * pDevice, ID3D11DeviceContext *	pContext, bool isVertexShader);
	void Deinit();

	void SetShaderBegin();

	void SetShaderVector4(const Vector4 & vector);
	void SetShaderMatrix4x4(const Matrix4x4 & matrix);

	void SetShaderEnd();
	
private:
	bool					m_isVertexShader;
	ID3D11Device *			m_pDevice;
	ID3D11DeviceContext *	m_pContext;
	ID3D11Buffer *			m_pConstantBuffer;
	std::vector<FLOAT>		m_constantBufferData;
	bool					m_recreateBuffer;

	typedef std::vector<FLOAT>::size_type size_t;
	
	size_t					m_startRegister;
};

#endif
