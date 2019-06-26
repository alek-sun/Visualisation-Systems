#include "DX9VertexShader.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9Convert.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/File.h"



D3DVERTEXELEMENT9 DX9Declaration[] =
{
	{0, 0,	D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
	{0, 12,	D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,		0},
	{0, 24,	D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0},
	{0, 28, D3DDECLTYPE_FLOAT2,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0},
	D3DDECL_END()
};


DX9VertexShader::DX9VertexShader(const char * fileName)
{
	m_isInited = false;

	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;

	m_pVShader = NULL;

	m_pDevice->CreateVertexDeclaration(DX9Declaration, &m_pVD);

	char * entryPoint = "main";
	//char * version = "vs_3_sw";
	char * version = "vs_3_0";
	DWORD flags = 0;
	LPD3DXBUFFER code = NULL;
	LPD3DXBUFFER errors = NULL;
	
	HRESULT hr = D3DXCompileShaderFromFileA(fileName, NULL, NULL, entryPoint, version, flags, &code, &errors, NULL);
	if( FAILED( hr ) )
	{
        char * pText = (char*) errors->GetBufferPointer();

        if (NULL != errors)
		{
			std::string title = "Error in " + File::GetFileName(fileName);
            MessageBoxA( NULL, pText, title.c_str(), MB_OK );
			errors->Release();
		}
        
		return;
	}

	hr = m_pDevice->CreateVertexShader((DWORD*) code->GetBufferPointer(), &m_pVShader);
	code->Release();

	m_isInited = true;
}

DX9VertexShader::DX9VertexShader(const unsigned long * pFunction)
{
	m_isInited = false;

	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;

	m_pVShader = NULL;

	m_pDevice->CreateVertexDeclaration(DX9Declaration, &m_pVD);
	m_pDevice->CreateVertexShader(pFunction, &m_pVShader);
}

bool DX9VertexShader::IsInited()
{
	return m_isInited;
}


void DX9VertexShader::SetShaderBegin()
{
	m_pDevice->SetVertexShader(m_pVShader);
	m_pDevice->SetVertexDeclaration(m_pVD);

	m_startRegister = 0;
	m_textureRegister = 0;
}

void DX9VertexShader::SetShaderVector4(Vector3 vector, float w)
{
	Vector4 vec4 = Vector4(vector, w);
	D3DXVECTOR4 vector4 = DX9Convert::ToDX9Vector4( vec4 );
	m_pDevice->SetVertexShaderConstantF(m_startRegister, vector4, 1);
	
	m_startRegister += 1;
}

void DX9VertexShader::SetShaderVector4(Vector4 vector)
{
	D3DXVECTOR4 vector4 = DX9Convert::ToDX9Vector4(vector);
	m_pDevice->SetVertexShaderConstantF(m_startRegister, vector4, 1);
	
	m_startRegister += 1;
}

void DX9VertexShader::SetShaderMatrix4x4(Matrix4x4 matrix)
{
	D3DXMATRIX matrixDX9 = DX9Convert::ToDX9Matrix4x4(matrix);
	m_pDevice->SetVertexShaderConstantF(m_startRegister, matrixDX9, 4);

	m_startRegister += 4;
}

void DX9VertexShader::SetShaderMatrix4x3(Matrix4x4 matrix)
{
	D3DXMATRIX matrixDX9 = DX9Convert::ToDX9Matrix4x4(matrix);
	m_pDevice->SetVertexShaderConstantF(m_startRegister, matrixDX9, 3);

	m_startRegister += 3;
}

// Передача на видеокарту Текстуры и Способа фильтрации (билинейная, анизотропная)
void DX9VertexShader::SetTexture(const Texture2D * pTexture)
{
	pTexture->PassToShader( m_textureRegister, false );

	m_textureRegister += 1;
}

void DX9VertexShader::SetShaderEnd()
{
	// умышленно оставлено пустым, 
	// чтобы сначала вызывали функцию SetShaderBegin()
	// потом функции SetShaderVector4(), SetShaderMatrix4x4()
}

#endif
