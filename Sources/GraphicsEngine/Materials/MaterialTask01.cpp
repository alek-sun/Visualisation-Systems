#include "MaterialTask01.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/GraphicsEngineFabric.h"


void MaterialTask01::Init(Object * pObject)
{
	Material::Init(pObject);
	
	pImpl = GraphicsEngineFabric::CreateFixedFunctionPipeline();
	pImpl->Init();
}

void MaterialTask01::Deinit()
{
	pImpl->Deinit();
	delete pImpl;
	pImpl = NULL;

	Material::Deinit();
}

void MaterialTask01::SetMaterial()
{
	// Заполняем матрицы World, View, Proj
	//const D3DXMATRIX & matWorld	= Convert::ToDX9Matrix4x4( SceneUtils::GetMatrixWorld(m_pObject) );
	//const D3DXMATRIX & matView	= Convert::ToDX9Matrix4x4( SceneUtils::GetMatrixView() );
	//const D3DXMATRIX & matProj	= Convert::ToDX9Matrix4x4( SceneUtils::GetMatrixProj() );
	//
	//m_pDevice->SetTransform( D3DTS_PROJECTION,	&matProj );
	//m_pDevice->SetTransform( D3DTS_VIEW,		&matView );
	//m_pDevice->SetTransform( D3DTS_WORLD,		&matWorld );
	
	const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(m_pObject);
	const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();

	pImpl->SetMatrixProjection( matProj );
	pImpl->SetMatrixView( matView );
	pImpl->SetMatrixWorld( matWorld );
}
