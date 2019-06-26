#include "DX9RenderTexture.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9TextureSampler.h"


DX9RenderTexture::DX9RenderTexture(int size)
	:	m_pDevice(NULL)
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;

	// TODO
}

DX9RenderTexture::~DX9RenderTexture()
{
	// TODO
}

void DX9RenderTexture::SetAsRenderTarget()
{
	// TODO
}

void DX9RenderTexture::RestoreRenderTarget()
{
	// TODO
}

void DX9RenderTexture::SetTexture(int textureRegister) const
{
	// TODO
}

#endif
