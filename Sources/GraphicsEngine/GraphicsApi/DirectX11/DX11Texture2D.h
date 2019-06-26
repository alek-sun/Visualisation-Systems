#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11.h"
#include "GraphicsEngine/GraphicsApi/Texture2DImpl.h"


// Read more
// http://www.3dgep.com/texturing-lighting-directx-11/
// https://msdn.microsoft.com/en-us/library/dn642451.aspx
// http://gamedev.stackexchange.com/questions/66231/set-sampler-states-linear-bilinear-trilinear-filtering-interpolation


/**
* @brief DX9Texture2D class is the implementation of the 2d-texture in DirectX 11.
*/
class DX11Texture2D : public Texture2DImpl
{
public:
	/**
	* @brief Constructs the object.
	* @param [in] filepath Full path of the file with the texture to load.
	*/
	DX11Texture2D(const char * filepath);

	/**
	* @brief Release resources.
	*/
	virtual ~DX11Texture2D();

	/**
	* @brief Pass texture to the pixel shader.
	* @param [in] textureRegister Position number in whole list of textures for the pixel shader.
	* @param [in] toPixelShader If is called from pixel shader then true, from vertex shader - false.
	*/
	void PassToShader(int textureRegister, bool toPixelShader) const;

private:
	ID3D11Device *				m_pDevice;
	ID3D11DeviceContext *		m_pContext;
	ID3D11ShaderResourceView *	m_pTexture;
};

#endif
