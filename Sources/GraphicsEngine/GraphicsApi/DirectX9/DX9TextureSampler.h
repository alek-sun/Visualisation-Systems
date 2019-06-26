#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9.h"
#include "GraphicsEngine/GraphicsApi/TextureSamplerImpl.h"


// Read more
// https://msdn.microsoft.com/en-us/library/windows/desktop/bb172615(v=vs.85).aspx
// http://www.toymaker.info/Games/html/textures.html
// https://msdn.microsoft.com/en-us/library/windows/desktop/bb172264(v=vs.85).aspx


/**
* @brief DX9TextureSampler class is the implementation for the texture sampler.
* It controls: filter mode, wrap mode, mip maps, anisotropy level.
*/
class DX9TextureSampler : public TextureSamplerImpl
{
public:
	/**
	* @brief Constructs the object.
	* @param [in] filterMode Texture filter mode (Point, Bilinear, Trilinear, Anisotropic).
	* @param [in] wrapMode Texture wrap mode (Clamp, Repeat).
	*/
	DX9TextureSampler(TextureFilterMode filterMode, TextureWrapMode wrapMode);
	
	// TODO: Make destructor virtual in the whole project
	
	/**
	* @brief Release resources.
	*/
	virtual ~DX9TextureSampler();

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
	LPDIRECT3DDEVICE9		m_pDevice;

	/**
	* @brief Texture filter mode (Point, Bilinear, Trilinear, Anisotropic).
	*/
	TextureFilterMode		m_filterMode;

	/**
	* @brief Texture wrap mode (Clamp, Repeat).
	*/
	TextureWrapMode			m_wrapMode;
	
	/**
	* @brief Texture filter mode in DirectX 9.
	*/
	D3DTEXTUREFILTERTYPE	m_filterModeDX9;

	D3DTEXTUREADDRESS		m_wrapModeDX9;
	
	/**
	* @brief Mip maps are enabled/disabled.
	*/
	bool					m_useMipMaps;

	/**
	* @brief Anisotropic filtering is enabled/disabled.
	*/
	bool					m_useAniso;
};

#endif
