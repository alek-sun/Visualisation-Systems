#include "DX11Texture2D.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11TextureSampler.h"


DX11Texture2D::DX11Texture2D(const char * filepath)
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX11GraphicsEngineContext * pDX11Context = static_cast<const DX11GraphicsEngineContext *>( pContext );
	m_pDevice = pDX11Context->m_pDevice;
	m_pContext = pDX11Context->m_pContext;

	// Load the Texture
	HRESULT hr = D3DX11CreateShaderResourceViewFromFileA( m_pDevice, filepath, NULL, NULL, &m_pTexture, NULL );
    if( FAILED( hr ) )
        return;

	m_pTextureSampler = new DX11TextureSampler( TEXTURE_FILTER_MODE_POINT, TEXTURE_WRAP_MODE_REPEAT );
}

DX11Texture2D::~DX11Texture2D()
{
	if (NULL != m_pTextureSampler)
	{
		delete m_pTextureSampler;
		m_pTextureSampler = NULL;
	}
	
	SAFE_RELEASE( m_pTexture );	
}

void DX11Texture2D::PassToShader(int textureRegister, bool toPixelShader) const
{
	if (toPixelShader)
	{
		m_pContext->PSSetShaderResources( textureRegister, 1, &m_pTexture );
	}
	else
	{
		m_pContext->VSSetShaderResources( textureRegister, 1, &m_pTexture );
	}

	m_pTextureSampler->PassParamsToShader( textureRegister, toPixelShader );
}

#endif
