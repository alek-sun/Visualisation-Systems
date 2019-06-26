#include "DX9PixelShader.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9Convert.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9RenderTexture.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/File.h"


DX9PixelShader::DX9PixelShader(const char * fileName)
{
	m_isInited = false;

	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;

	m_pPShader = NULL;

	char * entryPoint = "main";
	char * version = "ps_3_0";
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
	
	hr = m_pDevice->CreatePixelShader((DWORD*) code->GetBufferPointer(), &m_pPShader);
	code->Release();

	m_isInited = true;
}

DX9PixelShader::DX9PixelShader(const unsigned long * pFunction)
{
	m_isInited = false;

	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;

	m_pPShader = NULL;

	HRESULT hr = m_pDevice->CreatePixelShader(pFunction, &m_pPShader);
	int m = 0;
}

bool DX9PixelShader::IsInited()
{
	return m_isInited;
}


void DX9PixelShader::SetShaderBegin()
{
	m_pDevice->SetPixelShader(m_pPShader);
	
	m_startRegister		= 0;
	m_textureRegister	= 0;
}

void DX9PixelShader::SetShaderVector4(Vector3 vector, float w)
{
	D3DXVECTOR4 vector4 = DX9Convert::ToDX9Vector4( Vector4(vector, w) );
	m_pDevice->SetPixelShaderConstantF(m_startRegister, vector4, 1);	
	m_startRegister += 1;
}

void DX9PixelShader::SetShaderVector4(Vector4 vector)
{
	D3DXVECTOR4 vector4 = DX9Convert::ToDX9Vector4(vector);
	m_pDevice->SetPixelShaderConstantF(m_startRegister, vector4, 1);	
	m_startRegister += 1;
}

// TODO: По всему проекту заменить на const Matrix4x4 & matrix, и все похожие функции
void DX9PixelShader::SetShaderMatrix4x4(Matrix4x4 matrix)
{
	m_pDevice->SetPixelShaderConstantF(m_startRegister, DX9Convert::ToDX9Matrix4x4(matrix), 4);
	m_startRegister += 4;
}

void DX9PixelShader::SetShaderMatrix4x3(Matrix4x4 matrix)
{
	m_pDevice->SetPixelShaderConstantF(m_startRegister, DX9Convert::ToDX9Matrix4x4(matrix), 3);
	m_startRegister += 3;
}

// Передача на видеокарту Текстуры и Способа фильтрации (билинейная, анизотропная)
void DX9PixelShader::SetTexture(const Texture2D * pTexture)
{
	pTexture->PassToShader( m_textureRegister, true );

	m_textureRegister += 1;
}

void DX9PixelShader::SetTexture(const RenderTexture * pTexture)
{
	const DX9RenderTexture * pDX9Texture = static_cast<const DX9RenderTexture *>(pTexture->GetImplPointer());
	pDX9Texture->SetTexture(m_textureRegister);
	m_textureRegister += 1;
}

void DX9PixelShader::SetShaderEnd()
{
	// умышленно оставлено пустым, 
	// чтобы сначала вызывали функцию SetShaderBegin()
	// потом функции SetShaderVector4(), SetShaderMatrix4x4(), SetTexture()
}

#endif
