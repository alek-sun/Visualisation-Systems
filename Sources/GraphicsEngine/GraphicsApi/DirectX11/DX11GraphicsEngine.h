#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"
#include "GraphicsEngine/PlatformApi/Windows/WinWindow.h"
#include "GraphicsEngine/Matrix4x4.h"


class DX11GraphicsEngine : public GraphicsEngineImpl
{	
public:

	DX11GraphicsEngine();

	// Register class and create window
	void Init();
	
	// Clean up the objects we've created
	void Deinit();
		
	// Render a frame
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
	// Create Direct3D device and swap chain
	HRESULT InitDevice();

	WinWindow	m_window;

	const TCHAR * m_pWindowTitle;

	int m_width;
	int m_height;

	ID3D11Device *				m_pDevice;
	ID3D11DeviceContext *		m_pContext;
	IDXGISwapChain *			m_pSwapChain;
	ID3D11RenderTargetView *	m_pRenderTargetView;
	ID3D11Texture2D *			m_pDepthStencil;
	ID3D11DepthStencilView *	m_pDepthStencilView;
	ID3D11RasterizerState *		m_pRasterizerState;
	
	Rect	m_viewportRect;	
};

#endif
