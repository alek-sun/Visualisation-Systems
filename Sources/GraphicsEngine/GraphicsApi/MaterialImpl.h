#pragma once
#include "GraphicsEngine/Matrix4x4.h"
#include "GraphicsEngine/Texture2D.h"
#include "GraphicsEngine/RenderTexture.h"


class MaterialImpl
{
public:
	virtual ~MaterialImpl() { };

	virtual void Init() = 0;
	virtual void Deinit() = 0;
	virtual bool IsInited() = 0;

	virtual void SetMaterialBegin() = 0;

	virtual void SetVertexShaderBegin() = 0;
	virtual void SetVertexShaderMatrix4x4	(const char * propertyName, const Matrix4x4 & matrix) = 0;
	virtual void SetVertexShaderVector4		(const char * propertyName, const Vector4 & vector) = 0;
	virtual void SetVertexShaderTexture2d	(const char * propertyName, const Texture2D * pTexture) = 0;
	virtual void SetVertexShaderEnd() = 0;

	virtual void SetPixelShaderBegin() = 0;
	virtual void SetPixelShaderMatrix4x4	(const char * propertyName, const Matrix4x4 & matrix) = 0;
	virtual void SetPixelShaderVector4		(const char * propertyName, const Vector4 & vector) = 0;
	virtual void SetPixelShaderTexture2d	(const char * propertyName, const Texture2D * pTexture) = 0;
	virtual void SetPixelShaderTexture2d	(const char * propertyName, const RenderTexture * pTexture) = 0;
	virtual void SetPixelShaderEnd() = 0;

	virtual void SetMaterialEnd() = 0;

	virtual void ResetMaterial() = 0;
};
