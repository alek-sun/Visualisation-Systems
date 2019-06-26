#pragma once
#include "GraphicsEngine/Rect.h"
#include "GraphicsEngine/RenderTexture.h"
#include "GraphicsEngine/Vector3.h"


class GraphicsEngineImpl
{
public:
	virtual void Init() = 0;
	virtual void Deinit() = 0;

	virtual void Render() = 0;
	virtual bool IsRunning() = 0;

	/**
	* @brief Set the viewport for the current render target.
	* Current render target could be the screen (backbuffer) or a render texture.
	* Viewport is a rectangle area on the render target where is rendered image.
	* @param [in] rect Rectangle contains normalized coordinates of corners of the rendered image.
	* Normalized coordinates are coordinates that lay down in interval [0.0, 1.0].
	* @param [in] width Width of the render target in pixels.
	* @param [in] height Height of the render target in pixels.	
	*/
	virtual void SetViewport(Rect rect, int width, int height) = 0;

	/**
	* @brief Set the screen resolution (size of backbuffer).
	* @param [in] width Width of the screen in pixels.
	* @param [in] height Height of the screen in pixels.
	*/
	virtual void SetResolution(int width, int height) = 0;

	/**
	* @brief Set screen as the render target (draw objects to the screen).
	* @param [in] r,g,b Background color.
	*/
	virtual void SetRenderTarget(float r, float g, float b) = 0;

	/**
	* @brief Set render texture as the render target (draw objects to the render texture).
	* @param [in] renderTexture Render texture.
	*/
	virtual void SetRenderTarget(const RenderTexture * pRenderTexture) = 0;

	virtual void ResetRenderTarget(const RenderTexture * pRenderTexture) = 0;
};
