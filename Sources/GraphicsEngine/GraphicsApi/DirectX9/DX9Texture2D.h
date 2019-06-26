#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9.h"
#include "GraphicsEngine/GraphicsApi/Texture2DImpl.h"


/**
* @brief DX9Texture2D class is the implementation of the 2d-texture in DirectX 9.
*/
class DX9Texture2D : public Texture2DImpl
{
public:
	/**
	* @brief Constructs the object.
	* @param [in] filepath Full path of the file with the texture to load.
	*/
	DX9Texture2D(const char * filepath);

	/**
	* @brief Release resources.
	*/
	virtual ~DX9Texture2D();

	/**
	* @brief Pass texture to the pixel shader.
	* @param [in] textureRegister Position number in whole list of textures for the pixel shader.
	* @param [in] toPixelShader If is called from pixel shader then true, from vertex shader - false.
	*/
	void PassToShader(int textureRegister, bool toPixelShader) const;

private:
	LPDIRECT3DDEVICE9	m_pDevice;
	LPDIRECT3DTEXTURE9	m_pTexture;
};

#endif
