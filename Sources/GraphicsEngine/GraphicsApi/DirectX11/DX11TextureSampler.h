#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11.h"
#include "GraphicsEngine/GraphicsApi/TextureSamplerImpl.h"


// Read more
// http://www.3dgep.com/texturing-lighting-directx-11/
// https://msdn.microsoft.com/en-us/library/dn642451.aspx
// http://gamedev.stackexchange.com/questions/66231/set-sampler-states-linear-bilinear-trilinear-filtering-interpolation


/**
* @brief DX11TextureSampler class is the implementation for the texture sampler.
* It controls: filter mode, wrap mode, mip maps, anisotropy level.
*/
class DX11TextureSampler : public TextureSamplerImpl
{
public:
	/**
	* @brief Constructs the object.
	* @param [in] filterMode Texture filter mode (Point, Bilinear, Trilinear, Anisotropic).
	* @param [in] wrapMode Texture wrap mode (Clamp, Repeat).
	*/
	DX11TextureSampler(TextureFilterMode filterMode, TextureWrapMode wrapMode);

	/**
	* @brief Release resources.
	*/
	virtual ~DX11TextureSampler();

	/**
	* @brief Set texture filter mode (Point, Bilinear, Trilinear, Anisotropic).
	* @param [in] filterMode Texture filter mode.
	*/
	void SetFilterMode(TextureFilterMode filterMode);

	/**
	* @brief Set texture wrap mode (Clamp, Repeat).
	* @param [in] wrapMode Texture wrap mode.
	*/
	void SetWrapMode(TextureWrapMode wrapMode);

	/**
	* @brief Pass texture to the pixel shader.
	* Pass parameters: filter mode, wrap mode, mip maps, anisotropy level.
	* @param [in] textureRegister Position number in whole list of textures for the shader.
	* @param [in] toPixelShader If is called from pixel shader then true, from vertex shader - false.
	*/
	void PassParamsToShader(int textureRegister, bool toPixelShader) const;

private:
	void InitSamplerDesc();
	void CreateSamplerState();

	ID3D11Device *			m_pDevice;
	ID3D11DeviceContext *	m_pContext;

	/**
	* @brief Sampler state in DirectX 9.
	*/
	ID3D11SamplerState *	m_pSamplerState;

	D3D11_SAMPLER_DESC		m_samplerDesc;
};

#endif
