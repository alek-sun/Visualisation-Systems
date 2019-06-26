#include "MaterialRoad.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"


MaterialRoad::MaterialRoad(const Vector3 & color)
	:	m_color(color, 1)
{
	m_vsFileName = "ShaderRoad";
	m_psFileName = "ShaderRoad";
	m_pTexture1 = NULL;
	m_pTexture2 = NULL;
	m_pTexture3 = NULL;
}

void MaterialRoad::Init()
{
	Material::Init();
	m_pTexture1 = new Texture2D("road_1.jpg");
	m_pTexture2 = new Texture2D("road_2.jpg");
	m_pTexture3 = new Texture2D("road_3.jpg");
	m_pTexture1->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);
	//m_pTexture1->SetWrapMode(TEXTURE_WRAP_MODE_REPEAT);	
	m_pTexture2->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);	
	m_pTexture3->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);
	
}

void MaterialRoad::Deinit()
{
	Material::Deinit();
}

void MaterialRoad::SetMaterial(const Object * pObject)
{
	const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
	
	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4	("constColor", m_color);
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderTexture2d("texture1", m_pTexture1);
		SetPixelShaderTexture2d("texture2", m_pTexture2);
		SetPixelShaderTexture2d("texture3", m_pTexture3);
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
