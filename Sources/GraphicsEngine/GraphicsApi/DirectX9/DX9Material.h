#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/MaterialImpl.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9VertexShader.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9PixelShader.h"
#include "GraphicsEngine/Matrix4x4.h"
#include <string>


class DX9Material : public MaterialImpl
{
public:
	DX9Material(const char * vertexShaderFilePath, const char * fragmentShaderFilePath);
	~DX9Material();
	
	void Init();
	void Deinit();
	bool IsInited();

	void SetMaterialBegin();
	
	void SetVertexShaderBegin();
	void SetVertexShaderMatrix4x4	(const char * propertyName, const Matrix4x4 & matrix);
	void SetVertexShaderVector4		(const char * propertyName, const Vector4 & vector);
	void SetVertexShaderTexture2d	(const char * propertyName, const Texture2D * pTexture);
	void SetVertexShaderEnd();

	void SetPixelShaderBegin();
	void SetPixelShaderMatrix4x4	(const char * propertyName, const Matrix4x4 & matrix);
	void SetPixelShaderVector4		(const char * propertyName, const Vector4 & vector);
	void SetPixelShaderTexture2d	(const char * propertyName, const Texture2D * pTexture);
	void SetPixelShaderTexture2d	(const char * propertyName, const RenderTexture * pTexture);
	void SetPixelShaderEnd();

	void SetMaterialEnd();

	void ResetMaterial();
	
private:
	DX9VertexShader *	m_pVertexShader;
	DX9PixelShader *	m_pPixelShader;

	std::string			m_vsPath;
	std::string			m_psPath;
};

#endif
