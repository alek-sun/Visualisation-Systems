#pragma once
#include "GraphicsEngine/Materials/Material.h"


// Рассчитывает только компоненту diffuse от всех источников света
class MyMaterialDiffuse : public Material
{
public:
	MyMaterialDiffuse();

	virtual void Init();
	virtual void Deinit();
	
	virtual void SetMaterial(const Object * pObject);
};
