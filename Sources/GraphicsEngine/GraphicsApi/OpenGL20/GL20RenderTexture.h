#pragma once
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"


/**
* @brief RenderTextureImpl class is the implementation of render texture in OpenGL 2.0.
*/
class GL20RenderTexture : public RenderTextureImpl
{
public:
	GL20RenderTexture(int width, int height);
	~GL20RenderTexture();

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
	int		m_width;
	int		m_height;
};
