#pragma once
#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"


/**
* @brief Render texture class is used as a render target of camera.
*/
class RenderTexture
{
public:
	/**
	* @brief Constructs render texture.
	* @param [in] size Resolution of the render texture.
	*/
	RenderTexture(int size);
	~RenderTexture();

	/**
	* @brief Stores current render target and replace it by this render texture.
	* Scene will be rendered to this render texture.
	*/
	void SetAsRenderTarget() const;

	/**
	* @brief Sets current render target to the stored value.
	* Scene will be rendered to the restored render target (to the screen or to another render texture).
	*/
	void RestoreRenderTarget() const;

	/**
	* @brief The width of the render texture.
	*/
	int GetWidth() const;

	/**
	* @brief The height of the render texture.
	*/
	int GetHeight() const;

	const RenderTextureImpl * GetImplPointer() const;

private:
	RenderTextureImpl * m_pImpl;
	int m_size;
};
