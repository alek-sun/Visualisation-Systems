#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"
#include "GraphicsEngine/PlatformApi/Windows/WinWindow.h"


class DX9GraphicsEngine : public GraphicsEngineImpl
{
public:
	DX9GraphicsEngine();

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
	*/
	void SetRenderTarget(float r, float g, float b);

	/**
	* @brief Set render texture as the render target (draw objects to the render texture).
	*/
	void SetRenderTarget(const RenderTexture * pRenderTexture);

	void ResetRenderTarget(const RenderTexture * pRenderTexture);

private:
	HRESULT InitDevice();
	

	LPDIRECT3D9				m_pD3D;
	LPDIRECT3DDEVICE9		m_pDevice;
	D3DPRESENT_PARAMETERS	m_d3dpp;

	WinWindow	m_window;

	int m_width;
	int m_height;

	Scene & m_scene;
};

#endif
