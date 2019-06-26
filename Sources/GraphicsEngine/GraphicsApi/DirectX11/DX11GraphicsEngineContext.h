#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineContext.h"



class DX11GraphicsEngineContext : public GraphicsEngineContext
{
public:
	ID3D11Device *			m_pDevice;
	ID3D11DeviceContext *	m_pContext;

	DX11GraphicsEngineContext(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, GraphicsEngineImpl * pImpl)
		: GraphicsEngineContext(pImpl)
	{
		m_pDevice = pDevice;
		m_pContext = pContext;
	}
};

#endif
