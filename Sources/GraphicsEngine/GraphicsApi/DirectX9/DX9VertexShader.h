#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9.h"
#include "GraphicsEngine/GraphicsApi/VertexShaderImpl.h"


class DX9VertexShader : public VertexShaderImpl
{
public:
	DX9VertexShader(const char * fileName);
	DX9VertexShader(const unsigned long * pFunction);

	bool IsInited();

	void SetShaderBegin();
	
	// TODO: Во всём проекте передавать по возможности по ссылке: const Vector3 & vector
	void SetShaderVector4(Vector3 vector, float w);
	void SetShaderVector4(Vector4 vector);

	void SetShaderMatrix4x4(Matrix4x4 matrix);
	void SetShaderMatrix4x3(Matrix4x4 matrix);

	/**
	* @brief Pass texture to the shader.
	* @param [in] pTexture Pointer to the texture passed to the shader.
	*/
	void SetTexture(const Texture2D * pTexture);
	
	void SetShaderEnd();

private:
	bool m_isInited;

	LPDIRECT3DDEVICE9				m_pDevice;
	LPDIRECT3DVERTEXDECLARATION9	m_pVD;
	LPDIRECT3DVERTEXSHADER9			m_pVShader;
	
	int	m_startRegister;
	int m_textureRegister;
};

#endif
