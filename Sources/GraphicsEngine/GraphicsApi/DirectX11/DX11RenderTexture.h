#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11.h"
#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"


/**
* @brief RenderTextureImpl class is the implementation of render texture in DirectX 11.
*/
class DX11RenderTexture : public RenderTextureImpl
{
public:
	DX11RenderTexture(int size);
	~DX11RenderTexture();

	/**
	* @brief Stores current render target and replace it by this render texture.
	* Scene will be rendered to this render texture.
	*/
	void SetAsRenderTarget();

	/**
	* @brief Sets current render target to the stored value.
	* Scene will be rendered to the restored render target (to the screen or to another render texture).
	*/
	void RestoreRenderTarget();

	/**
	* @brief Pass texture to the pixel shader.
	* @param [in] textureRegister Position number in whole list of textures for the pixel shader.
	*/
	void SetTexture(int textureRegister) const;

private:
	ID3D11Device *				m_pDevice;
	ID3D11DeviceContext *		m_pContext;
};

#endif
