#pragma once
#include "GraphicsEngine/GraphicsApi/TextureImpl.h"


/**
* @brief RenderTextureImpl class is the interface for render textures.
*/
class RenderTextureImpl : public TextureImpl
{
public:
	/**
	* @brief Stores current render target and replace it by this render texture.
	* Scene will be rendered to this render texture.
	*/
	virtual void SetAsRenderTarget() = 0;

	/**
	* @brief Sets current render target to the stored value.
	* Scene will be rendered to the restored render target (to the screen or to another render texture).
	*/
	virtual void RestoreRenderTarget() = 0;
};
