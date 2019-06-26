#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11.h"
#include "GraphicsEngine/GraphicsApi/PixelShaderImpl.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11ConstantBuffer.h"


class DX11PixelShader : public PixelShaderImpl
{
public:
	// TODO: Заменить в проекте LPCWSTR на LPCTSTR
	DX11PixelShader(const char * fileName);
	DX11PixelShader(const unsigned long * pFunction);

	bool IsInited();

	void SetShaderBegin();

	void SetShaderVector4(Vector3 vector, float w);
	void SetShaderVector4(Vector4 vector);

	void SetShaderMatrix4x4(Matrix4x4 matrix);
	void SetShaderMatrix4x3(Matrix4x4 matrix);

	/**
	* @brief Pass texture to the shader.
	* @param [in] pTexture Pointer to the texture passed to the shader.
	*/
	void SetTexture(const Texture2D * pTexture);
	
	/**
	* @brief Pass texture to the shader.
	* @param [in] pTexture Pointer to the texture passed to the shader.
	*/
	void SetTexture(const RenderTexture * pTexture);

	void SetShaderEnd();

private:
	bool m_isInited;

	ID3D11Device *			m_pDevice;
	ID3D11DeviceContext *	m_pContext;
	ID3D11PixelShader *		m_pPixelShader;
	DX11ConstantBuffer		m_constantBuffer;
	
	int m_textureRegister;
};

#endif
