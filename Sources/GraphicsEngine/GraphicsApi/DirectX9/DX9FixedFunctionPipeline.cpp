#include "DX9FixedFunctionPipeline.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9Convert.h"


void DX9FixedFunctionPipeline::Init()
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;
}

void DX9FixedFunctionPipeline::Deinit()
{
	m_pDevice = NULL;
}

void DX9FixedFunctionPipeline::SetMatrixWorld(const Matrix4x4 & matrix)
{
	const D3DXMATRIX & matWorld	= DX9Convert::ToDX9Matrix4x4( matrix );
	m_pDevice->SetTransform( D3DTS_WORLD, &matWorld );
}

void DX9FixedFunctionPipeline::SetMatrixView(const Matrix4x4 & matrix)
{
	const D3DXMATRIX & matView	= DX9Convert::ToDX9Matrix4x4( matrix );
	m_pDevice->SetTransform( D3DTS_VIEW, &matView );
}

void DX9FixedFunctionPipeline::SetMatrixProjection(const Matrix4x4 & matrix)
{
	const D3DXMATRIX & matProj	= DX9Convert::ToDX9Matrix4x4( matrix );
	m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

#endif
