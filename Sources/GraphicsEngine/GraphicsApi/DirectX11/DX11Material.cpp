#include "DX11Material.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"


DX11Material::DX11Material(const char * vertexShaderFilePath, const char * fragmentShaderFilePath)
{
	std::string shadersDirectory = Application::Instance().GetShadersDirectory();
	m_vsPath = shadersDirectory + "DX11/" +  std::string(vertexShaderFilePath)   + ".fx";
	m_psPath = shadersDirectory + "DX11/" +  std::string(fragmentShaderFilePath) + ".fx";

	Init();
}

DX11Material::~DX11Material()
{
	Deinit();
}
	
void DX11Material::Init()
{
	m_pVertexShader	= new DX11VertexShader( m_vsPath.c_str() );
	m_pPixelShader	= new DX11PixelShader ( m_psPath.c_str() );
}

void DX11Material::Deinit()
{
	delete m_pPixelShader;
	m_pPixelShader = NULL;

	delete m_pVertexShader;
	m_pVertexShader = NULL;
}

bool DX11Material::IsInited()
{
	bool vs = m_pVertexShader->IsInited();
	bool ps = m_pPixelShader->IsInited();

	return (vs && ps);
}


void DX11Material::SetMaterialBegin()
{

}
	
void DX11Material::SetVertexShaderBegin()
{
	m_pVertexShader->SetShaderBegin();
}

void DX11Material::SetVertexShaderMatrix4x4(const char * propertyName, const Matrix4x4 & matrix)
{
	m_pVertexShader->SetShaderMatrix4x4(matrix);
}

void DX11Material::SetVertexShaderVector4(const char * propertyName, const Vector4 & vector)
{
	m_pVertexShader->SetShaderVector4(vector);
}

void DX11Material::SetVertexShaderTexture2d(const char * propertyName, const Texture2D * pTexture)
{
	m_pVertexShader->SetTexture(pTexture);
}

void DX11Material::SetVertexShaderEnd()
{
	m_pVertexShader->SetShaderEnd();
}


void DX11Material::SetPixelShaderBegin()
{
	m_pPixelShader->SetShaderBegin();
}

void DX11Material::SetPixelShaderMatrix4x4(const char * propertyName, const Matrix4x4 & matrix)
{
	m_pPixelShader->SetShaderMatrix4x4(matrix);
}

void DX11Material::SetPixelShaderVector4(const char * propertyName, const Vector4 & vector)
{
	m_pPixelShader->SetShaderVector4(vector);
}

void DX11Material::SetPixelShaderTexture2d(const char * propertyName, const Texture2D * pTexture)
{
	m_pPixelShader->SetTexture(pTexture);
}

void DX11Material::SetPixelShaderTexture2d(const char * propertyName, const RenderTexture * pTexture)
{
	m_pPixelShader->SetTexture(pTexture);
}

void DX11Material::SetPixelShaderEnd()
{
	m_pPixelShader->SetShaderEnd();
}

void DX11Material::SetMaterialEnd()
{

}

void DX11Material::ResetMaterial()
{

}

#endif
