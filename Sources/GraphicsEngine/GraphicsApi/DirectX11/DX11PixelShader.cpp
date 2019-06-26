#include "DX11PixelShader.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11RenderTexture.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/File.h"

//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
// TODO: Убрать дублирующие функции
HRESULT CompileShaderFromFile2( const char * fileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFileA( fileName, NULL, NULL, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
    if( FAILED( hr ) )
	{
        char * pText = (char*) pErrorBlob->GetBufferPointer();

        if (NULL != pErrorBlob)
		{
			std::string title = "Error in " + File::GetFileName(fileName);
            MessageBoxA( NULL, pText, title.c_str(), MB_OK );
			pErrorBlob->Release();
		}
        
		return hr;
	}

    return S_OK;
}


DX11PixelShader::DX11PixelShader(const char * fileName)
	:	m_pDevice		(NULL),
		m_pContext		(NULL),
		m_pPixelShader	(NULL)
{
	m_isInited = false;

	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX11GraphicsEngineContext * pContextDX11 = static_cast<const DX11GraphicsEngineContext *>( pContext );
	m_pDevice = pContextDX11->m_pDevice;
	m_pContext	= pContextDX11->m_pContext;

	// Compile the pixel shader
	HRESULT hr = S_OK;
	ID3DBlob* pPSBlob = NULL;
    hr = CompileShaderFromFile2( fileName, "PS", "ps_4_0", &pPSBlob );
    if( FAILED( hr ) )
    {
        //MessageBox( NULL, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return;
    }

	// Create the pixel shader
	hr = m_pDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &m_pPixelShader );
	pPSBlob->Release();
    if( FAILED( hr ) )
        return;

	m_constantBuffer.Init(m_pDevice, m_pContext, false);

	m_isInited = true;
}

DX11PixelShader::DX11PixelShader(const unsigned long * pFunction)
	:	m_pDevice		(NULL),
		m_pContext		(NULL),
		m_pPixelShader	(NULL)
{
	m_isInited = false;

	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX11GraphicsEngineContext * pContextDX11 = static_cast<const DX11GraphicsEngineContext *>( pContext );
	m_pDevice = pContextDX11->m_pDevice;
	m_pContext	= pContextDX11->m_pContext;

	//HRESULT hr = m_pDevice->CreatePixelShader(pFunction, &m_pPShader);
	//int m = 0;
}

bool DX11PixelShader::IsInited()
{
	return m_isInited;
}


void DX11PixelShader::SetShaderBegin()
{
	m_constantBuffer.SetShaderBegin();

	m_textureRegister = 0;
}

void DX11PixelShader::SetShaderVector4(Vector3 vector, float w)
{
	m_constantBuffer.SetShaderVector4( Vector4(vector, w) );
}

void DX11PixelShader::SetShaderVector4(Vector4 vector)
{
	m_constantBuffer.SetShaderVector4(vector);
}

// TODO: По всему проекту заменить на const Matrix4x4 & matrix, и все похожие функции
void DX11PixelShader::SetShaderMatrix4x4(Matrix4x4 matrix)
{
	m_constantBuffer.SetShaderMatrix4x4(matrix);
}

void DX11PixelShader::SetShaderMatrix4x3(Matrix4x4 matrix)
{
	//m_pDevice->SetPixelShaderConstantF(m_startRegister, Convert::ToDX9Matrix4x4(matrix), 3);

	//m_startRegister += 3;
}

void DX11PixelShader::SetTexture(const Texture2D * pTexture)
{
	pTexture->PassToShader( m_textureRegister, true );

	m_textureRegister += 1;
}

void DX11PixelShader::SetTexture(const RenderTexture * pTexture)
{
	const DX11RenderTexture * pDX11Texture = static_cast<const DX11RenderTexture *>(pTexture->GetImplPointer());
	pDX11Texture->SetTexture( m_textureRegister );
	m_textureRegister += 1;
}

void DX11PixelShader::SetShaderEnd()
{
	m_constantBuffer.SetShaderEnd();

	m_pContext->PSSetShader( m_pPixelShader, NULL, 0 );
}

#endif
