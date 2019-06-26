#pragma once
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"
#include "GraphicsEngine/Scene.h"


class GL20GraphicsEngine : public GraphicsEngineImpl
{
public:
	GL20GraphicsEngine();

	void Init();
	void Deinit();

	void Render();
	bool IsRunning();

	/**
	* @brief Set the viewport for the current render target.
	* Current render target could be the screen (backbuffer) or a render texture.
	* Viewport is a rectangle area on the render target where is rendered image.
	* @param [in] rect Rectangle contains normalized coordinates of corners of the rendered image.
	* Normalized coordinates are coordinates that lay down in interval [0.0, 1.0].
	* @param [in] width Width of the render target in pixels.
	* @param [in] height Height of the render target in pixels.	
	*/
	void SetViewport(Rect rect, int width, int height);

	/**
	* @brief Set the screen resolution (size of backbuffer).
	* @param [in] width Width of the screen in pixels.
	* @param [in] height Height of the screen in pixels.
	*/
	void SetResolution(int width, int height);

	/**
	* @brief Set screen as the render target (draw objects to the screen).
	* @param [in] r,g,b Background color.
	*/
	void SetRenderTarget(float r, float g, float b);

	/**
	* @brief Set render texture as the render target (draw objects to the render texture).
	* @param [in] pRenderTexture Render texture pointer.
	*/
	void SetRenderTarget(const RenderTexture * pRenderTexture);

	void ResetRenderTarget(const RenderTexture * pRenderTexture);

	// TODO: —делать private
	void Render1();
	void Reshape(int w, int h);

private:
	const char * m_pWindowTitle;
	int m_window;
	
	Rect m_viewportRect;

	Scene & m_scene;
};
