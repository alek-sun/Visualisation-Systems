#include "DX11TextureSampler.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsEngineContext.h"


DX11TextureSampler::DX11TextureSampler(TextureFilterMode filterMode, TextureWrapMode wrapMode)
	:	m_pSamplerState(NULL)
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX11GraphicsEngineContext * pDX11Context = static_cast<const DX11GraphicsEngineContext *>( pContext );
	m_pDevice = pDX11Context->m_pDevice;
	m_pContext = pDX11Context->m_pContext;

	InitSamplerDesc();
	SetFilterMode( filterMode );
	SetWrapMode  ( wrapMode );
}

DX11TextureSampler::~DX11TextureSampler()
{
	SAFE_RELEASE( m_pSamplerState );
}

void DX11TextureSampler::SetFilterMode(TextureFilterMode filterMode)
{
	if (filterMode == TEXTURE_FILTER_MODE_POINT)
	{
		// TODO: Task05_01
	}
	else if (filterMode == TEXTURE_FILTER_MODE_BILINEAR)
	{
		// TODO: Task05_01
	}
	else if (filterMode == TEXTURE_FILTER_MODE_TRILINEAR)
	{
		// TODO: Task05_01
	}
	else if (filterMode == TEXTURE_FILTER_MODE_ANISOTROPIC)
	{
		// TODO: Task05_01
	}	
	
	CreateSamplerState();
}

void DX11TextureSampler::SetWrapMode(TextureWrapMode wrapMode)
{
	if (wrapMode == TEXTURE_WRAP_MODE_CLAMP)
	{
		// TODO: Task05_01
	}
	else if (wrapMode == TEXTURE_WRAP_MODE_REPEAT)
	{
		// TODO: Task05_01
	}

	CreateSamplerState();
}

void DX11TextureSampler::PassParamsToShader(int textureRegister, bool toPixelShader) const
{
	if (toPixelShader)
	{
		m_pContext->PSSetSamplers( textureRegister, 1, &m_pSamplerState );
	}
	else
	{
		m_pContext->VSSetSamplers( textureRegister, 1, &m_pSamplerState );
	}
}

void DX11TextureSampler::InitSamplerDesc()
{
	// Init the sampler desc for the first time
	ZeroMemory( &m_samplerDesc, sizeof(m_samplerDesc) );
	m_samplerDesc.Filter			= D3D11_FILTER_MIN_MAG_MIP_POINT;
	m_samplerDesc.AddressU			= D3D11_TEXTURE_ADDRESS_WRAP;
	m_samplerDesc.AddressV			= D3D11_TEXTURE_ADDRESS_WRAP;
	m_samplerDesc.AddressW			= D3D11_TEXTURE_ADDRESS_WRAP;
	//m_samplerDesc.ComparisonFunc	= D3D11_COMPARISON_NEVER;
	m_samplerDesc.ComparisonFunc	= D3D11_COMPARISON_LESS;
	m_samplerDesc.MinLOD			= 0;
	m_samplerDesc.MaxLOD			= 0;
	m_samplerDesc.MaxAnisotropy		= 0;
}

void DX11TextureSampler::CreateSamplerState()
{
	SAFE_RELEASE( m_pSamplerState );

	HRESULT hr = m_pDevice->CreateSamplerState( &m_samplerDesc, &m_pSamplerState );
	if ( FAILED( hr ) )
	{
		m_pSamplerState = NULL;
	}
}

#endif
