#include "DX9Material.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/File.h"


DX9Material::DX9Material(const char * vertexShaderFilePath, const char * fragmentShaderFilePath)
{
	std::string shadersDirectory = Application::Instance().GetShadersDirectory();
	
	//m_vsPath = shadersDirectory + "DX9/" + std::string(vertexShaderFilePath)   + ".fx";
	//m_psPath = shadersDirectory + "DX9/" + std::string(fragmentShaderFilePath) + ".fx";
	
	//if ( !File::Exists( m_vsPath ) )
	{
		m_vsPath = shadersDirectory + "DX9/" + std::string(vertexShaderFilePath)   + ".vs";
		m_psPath = shadersDirectory + "DX9/" + std::string(fragmentShaderFilePath) + ".ps";
	}
	
	Init();
}

DX9Material::~DX9Material()
{
	Deinit();
}
	
void DX9Material::Init()
{
	m_pVertexShader	= new DX9VertexShader( m_vsPath.c_str() );
	m_pPixelShader	= new DX9PixelShader ( m_psPath.c_str() );
}

void DX9Material::Deinit()
{
	delete m_pPixelShader;
	m_pPixelShader = NULL;

	delete m_pVertexShader;
	m_pVertexShader = NULL;
}

bool DX9Material::IsInited()
{
	bool vs = m_pVertexShader->IsInited();
	bool ps = m_pPixelShader->IsInited();

	return (vs && ps);
}


void DX9Material::SetMaterialBegin()
{

}
	
void DX9Material::SetVertexShaderBegin()
{
	m_pVertexShader->SetShaderBegin();
}

void DX9Material::SetVertexShaderMatrix4x4(const char * propertyName, const Matrix4x4 & matrix)
{
	m_pVertexShader->SetShaderMatrix4x4(matrix);
}

void DX9Material::SetVertexShaderVector4(const char * propertyName, const Vector4 & vector)
{
	m_pVertexShader->SetShaderVector4(vector);
}

void DX9Material::SetVertexShaderTexture2d(const char * propertyName, const Texture2D * pTexture)
{
	m_pVertexShader->SetTexture(pTexture);
}

void DX9Material::SetVertexShaderEnd()
{
	m_pVertexShader->SetShaderEnd();
}

void DX9Material::SetPixelShaderBegin()
{
	m_pPixelShader->SetShaderBegin();
}

void DX9Material::SetPixelShaderMatrix4x4(const char * propertyName, const Matrix4x4 & matrix)
{
	m_pPixelShader->SetShaderMatrix4x4(matrix);
}

void DX9Material::SetPixelShaderVector4(const char * propertyName, const Vector4 & vector)
{
	m_pPixelShader->SetShaderVector4(vector);
}

void DX9Material::SetPixelShaderTexture2d(const char * propertyName, const Texture2D * pTexture)
{
	m_pPixelShader->SetTexture(pTexture);
}

void DX9Material::SetPixelShaderTexture2d(const char * propertyName, const RenderTexture * pTexture)
{
	m_pPixelShader->SetTexture(pTexture);
}

void DX9Material::SetPixelShaderEnd()
{
	m_pPixelShader->SetShaderEnd();
}

void DX9Material::SetMaterialEnd()
{

}

void DX9Material::ResetMaterial()
{

}

#endif
