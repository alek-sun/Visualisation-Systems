#include "MaterialSand3.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"


MaterialSand3::MaterialSand3(TextureFilterMode filterMode)
{
	m_vsFileName = "ShaderSand3";
	m_psFileName = "ShaderSand3";

	m_pTexture1 = NULL;
	m_filterMode = filterMode;
}

void MaterialSand3::Init()
{
	Material::Init();

	m_pTexture1 = new Texture2D("road_3.jpg");
			
	m_pTexture1->SetFilterMode(m_filterMode);
}

void MaterialSand3::Deinit()
{
	delete m_pTexture1;
	m_pTexture1 = NULL;

	Material::Deinit();
}

void MaterialSand3::SetMaterial(const Object * pObject)
{
	const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
	
	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 1));
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderTexture2d("texture1", m_pTexture1);
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
