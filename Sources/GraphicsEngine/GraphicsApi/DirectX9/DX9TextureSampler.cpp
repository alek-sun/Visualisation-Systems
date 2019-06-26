#include "DX9TextureSampler.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"


DX9TextureSampler::DX9TextureSampler(TextureFilterMode filterMode, TextureWrapMode wrapMode)
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;

	SetFilterMode( filterMode );
	SetWrapMode  ( wrapMode );
}

DX9TextureSampler::~DX9TextureSampler()
{
	
}

void DX9TextureSampler::SetFilterMode(TextureFilterMode filterMode)
{
	m_filterMode = filterMode;

	if (m_filterMode == TEXTURE_FILTER_MODE_POINT)
	{
		// TODO: Task05_01
	}
	else if (m_filterMode == TEXTURE_FILTER_MODE_BILINEAR)
	{
		// TODO: Task05_01
	}
	else if (m_filterMode == TEXTURE_FILTER_MODE_TRILINEAR)
	{
		// TODO: Task05_01
	}
	else if (m_filterMode == TEXTURE_FILTER_MODE_ANISOTROPIC)
	{
		// TODO: Task05_01
	}	
}

void DX9TextureSampler::SetWrapMode(TextureWrapMode wrapMode)
{
	m_wrapMode = wrapMode;

	if (m_wrapMode == TEXTURE_WRAP_MODE_CLAMP)
	{
		// TODO: Task05_01
	}
	else if (m_wrapMode == TEXTURE_WRAP_MODE_REPEAT)
	{
		// TODO: Task05_01
	}
}

void DX9TextureSampler::PassParamsToShader(int textureRegister, bool toPixelShader) const
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/bb174456(v=vs.85).aspx
	DWORD sampler = textureRegister;

	if (!toPixelShader)
	{
		// https://msdn.microsoft.com/en-us/library/windows/desktop/bb206339(v=vs.85).aspx#Sampling_Stage_Registers
		sampler += D3DVERTEXTEXTURESAMPLER0;
	}

	// Set wrap mode (Clamp, Repeat) 
	// TODO: Task05_01


	// Set filter mode (Point, Bilinear, Trilinear, Anisotropic)
	// TODO: Task05_01
	
	// Set degree of anisotropic filtering (aniso level)
	if (m_useAniso)
	{
		// TODO: Task05_01
	}
	else
	{
		// TODO: Task05_01
	}
	
	// Enable/Disable mip maps
	if (m_useMipMaps)
	{
		// TODO: Task05_01
	}
	else
	{
		// TODO: Task05_01
	}
}

#endif
