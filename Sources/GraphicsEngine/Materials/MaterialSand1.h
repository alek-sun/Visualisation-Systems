#pragma once
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Texture2D.h"


class MaterialSand1 : public Material
{
public:
	MaterialSand1(TextureFilterMode filterMode);

	virtual void Init();
	virtual void Deinit();
	
	virtual void SetMaterial(const Object * pObject);

private:
	Texture2D *	m_pTexture1;
	TextureFilterMode m_filterMode;
};
