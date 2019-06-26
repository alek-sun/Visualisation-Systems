#include "DX9Texture2D.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9TextureSampler.h"


DX9Texture2D::DX9Texture2D(const char * filepath)
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;

	D3DXCreateTextureFromFileA( m_pDevice, filepath, &m_pTexture );
	//HRESULT hr = D3DXCreateTextureFromFileExA( m_pDevice, filepath, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 
	//								D3DUSAGE_DYNAMIC, D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, 
	//								D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &m_pTexture );

	m_pTextureSampler = new DX9TextureSampler( TEXTURE_FILTER_MODE_POINT, TEXTURE_WRAP_MODE_REPEAT );
}

DX9Texture2D::~DX9Texture2D()
{
	if (NULL != m_pTextureSampler)
	{
		delete m_pTextureSampler;
		m_pTextureSampler = NULL;
	}

	SAFE_RELEASE( m_pTexture );
}

void DX9Texture2D::PassToShader(int textureRegister, bool toPixelShader) const
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/bb174461(v=vs.85).aspx
	DWORD sampler = textureRegister;

	if ( !toPixelShader )
	{
		// https://msdn.microsoft.com/en-us/library/windows/desktop/bb206339(v=vs.85).aspx#Sampling_Stage_Registers
		sampler += D3DVERTEXTEXTURESAMPLER0;
	}

	HRESULT hr = m_pDevice->SetTexture( sampler, m_pTexture );
	
	m_pTextureSampler->PassParamsToShader( textureRegister, toPixelShader );
}

#endif
