#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9.h"
#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"


/**
* @brief RenderTextureImpl class is the implementation of render texture in DirectX 9.
*/
class DX9RenderTexture : public RenderTextureImpl
{
public:
	DX9RenderTexture(int size);
	~DX9RenderTexture();

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
	LPDIRECT3DDEVICE9		m_pDevice;	
};

#endif
