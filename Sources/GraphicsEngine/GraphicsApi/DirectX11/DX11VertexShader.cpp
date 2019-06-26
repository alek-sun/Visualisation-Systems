#include "DX11VertexShader.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsEngineContext.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/File.h"


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile1( const char * fileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
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


DX11VertexShader::DX11VertexShader(const char * fileName)
	:	m_pDevice		(NULL),
		m_pContext		(NULL),
		m_pVertexShader	(NULL),
		m_pVertexLayout	(NULL)
{
	m_isInited = false;

	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX11GraphicsEngineContext * pContextDX11 = static_cast<const DX11GraphicsEngineContext *>( pContext );
	m_pDevice = pContextDX11->m_pDevice;
	m_pContext	= pContextDX11->m_pContext;

	// Compile the vertex shader
	HRESULT hr = S_OK;
	ID3DBlob* pVSBlob = NULL;
    hr = CompileShaderFromFile1( fileName, "VS", "vs_4_0", &pVSBlob );
    if( FAILED( hr ) )
    {
        return;
    }

	// Create the vertex shader
	hr = m_pDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &m_pVertexShader );
	if( FAILED( hr ) )
	{	
		pVSBlob->Release();
        return;
	}

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 12,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 24,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 40,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE( layout );

    // Create the input layout
	hr = m_pDevice->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
                                          pVSBlob->GetBufferSize(), &m_pVertexLayout );
	pVSBlob->Release();
	if( FAILED( hr ) )
        return;

	m_constantBuffer.Init(m_pDevice, m_pContext, true);

	m_isInited = true;
}

DX11VertexShader::DX11VertexShader(const unsigned long * pFunction)
	:	m_pDevice		(NULL),
		m_pContext		(NULL),
		m_pVertexShader	(NULL),
		m_pVertexLayout	(NULL)
{
	m_isInited = false;

	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX11GraphicsEngineContext * pContextDX11 = static_cast<const DX11GraphicsEngineContext *>( pContext );
	m_pDevice	= pContextDX11->m_pDevice;
	m_pContext	= pContextDX11->m_pContext;
}

bool DX11VertexShader::IsInited()
{
	return m_isInited;
}


void DX11VertexShader::SetShaderBegin()
{
	m_constantBuffer.SetShaderBegin();
	m_textureRegister = 0;
}

void DX11VertexShader::SetShaderVector4(Vector3 vector, float w)
{
	m_constantBuffer.SetShaderVector4( Vector4(vector, w) );
}

void DX11VertexShader::SetShaderVector4(Vector4 vector)
{
	m_constantBuffer.SetShaderVector4(vector);
}

void DX11VertexShader::SetShaderMatrix4x4(Matrix4x4 matrix)
{
	m_constantBuffer.SetShaderMatrix4x4(matrix);
}

void DX11VertexShader::SetShaderMatrix4x3(Matrix4x4 matrix)
{
	//D3DXMATRIX matrixDX9 = Convert::ToDX9Matrix4x4(matrix);
	//m_pDevice->SetVertexShaderConstantF(m_startRegister, matrixDX9, 3);

	//m_startRegister += 3;
}

void DX11VertexShader::SetTexture(const Texture2D * pTexture)
{
	pTexture->PassToShader( m_textureRegister, false );

	m_textureRegister += 1;
}

void DX11VertexShader::SetShaderEnd()
{
	m_constantBuffer.SetShaderEnd();

	m_pContext->VSSetShader( m_pVertexShader, NULL, 0 );

	// Set the input layout
	m_pContext->IASetInputLayout( m_pVertexLayout );
}

#endif
