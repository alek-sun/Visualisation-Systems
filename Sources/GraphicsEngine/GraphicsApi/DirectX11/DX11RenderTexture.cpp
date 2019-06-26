#include "DX11RenderTexture.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11TextureSampler.h"


DX11RenderTexture::DX11RenderTexture(int size)
	:	m_pDevice(NULL),
		m_pContext(NULL)
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX11GraphicsEngineContext * pDX11Context = static_cast<const DX11GraphicsEngineContext *>( pContext );
	m_pDevice	= pDX11Context->m_pDevice;
	m_pContext	= pDX11Context->m_pContext;

	// TODO
}

DX11RenderTexture::~DX11RenderTexture()
{
	// TODO
}

void DX11RenderTexture::SetAsRenderTarget()
{
	// TODO
}

void DX11RenderTexture::RestoreRenderTarget()
{
	// TODO
}

void DX11RenderTexture::SetTexture(int textureRegister) const
{
	// TODO
}

#endif
