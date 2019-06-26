#include "DX11GraphicsEngine.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsEngineContext.h"


// Called every time the application receives a message
LRESULT CALLBACK DX11WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
	}

	return DefWindowProc( hWnd, message, wParam, lParam );
}


DX11GraphicsEngine::DX11GraphicsEngine()
	:	m_window( TEXT("Graphics Engine (DirectX 11)") ),
		m_pDevice(NULL),
		m_pContext(NULL),
		m_pSwapChain(NULL),
		m_pRenderTargetView(NULL),
		m_pDepthStencil(NULL),
		m_pDepthStencilView(NULL)
{
	
}

void DX11GraphicsEngine::Init()
{
	m_window.Init(this);
		
	// Initialize Direct3D
	if( SUCCEEDED( InitDevice() ) )
	{
		m_window.Show();
	}

	Application::Instance().GetScene().Init();
}

void DX11GraphicsEngine::Deinit()
{
	Application::Instance().GetScene().Deinit();

	if( m_pRasterizerState )	m_pRasterizerState->Release();
	if( m_pContext )			m_pContext->ClearState();
	if( m_pDepthStencil )		m_pDepthStencil->Release();
	if( m_pDepthStencilView )	m_pDepthStencilView->Release();
	if( m_pRenderTargetView )	m_pRenderTargetView->Release();
	if( m_pSwapChain )			m_pSwapChain->Release();
	if( m_pContext )			m_pContext->Release();
	if( m_pDevice )				m_pDevice->Release();

	m_window.Deinit();
}

void DX11GraphicsEngine::Render()
{
	m_window.DispatchMessages();
    
	if (IsRunning())
	{
		{
			Scene & m_scene = Application::Instance().GetScene();
			m_scene.Update();
			m_scene.Render();
		}

		// Present our back buffer to our front buffer
		//m_pSwapChain->Present( 0, 0 );
	}	
}

bool DX11GraphicsEngine::IsRunning()
{
	//return (m_msg.message != WM_QUIT);
	return m_window.IsRunning();
}

void DX11GraphicsEngine::SetViewport(Rect rect, int width, int height)
{
	// https://msdn.microsoft.com/ru-ru/library/windows/desktop/bb205126(v=vs.85).aspx
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ff476480(v=vs.85).aspx

	m_viewportRect = rect;

	D3D11_VIEWPORT vp;
	{
		vp.TopLeftX	= static_cast<FLOAT>( m_viewportRect.x * width  );
		vp.TopLeftY	= static_cast<FLOAT>( m_viewportRect.y * height );
		vp.Width	= static_cast<FLOAT>( m_viewportRect.w * width  );
		vp.Height	= static_cast<FLOAT>( m_viewportRect.h * height );
		vp.MinDepth	= 0.0f;
		vp.MaxDepth	= 1.0f;
	}

	m_pContext->RSSetViewports( 1, &vp );
}

void DX11GraphicsEngine::SetResolution(int width, int height)
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/bb205075(v=vs.85).aspx#Handling_Window_Resizing

	if (m_width == width && m_height == height)
	{
		return;
	}

	m_width	= width;
	m_height = height;

	m_pContext->OMSetRenderTargets(0, 0, 0);
	{
		// Release all outstanding references to the swap chain's buffers.
		m_pRenderTargetView->Release();

		HRESULT hr;
		// Preserve the existing buffer count and format.
		// Automatically choose the width and height to match the client rect for HWNDs.
		hr = m_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
                                            
		// Perform error handling here!

		// Get buffer and create a render-target-view.
		ID3D11Texture2D* pBuffer;
		hr = m_pSwapChain->GetBuffer(0, __uuidof( ID3D11Texture2D), (void**) &pBuffer );
		// Perform error handling here!

		hr = m_pDevice->CreateRenderTargetView(pBuffer, NULL, &m_pRenderTargetView);
		// Perform error handling here!
		pBuffer->Release();
	}
    m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL );

    SetViewport(m_viewportRect, m_width, m_height);
}

void DX11GraphicsEngine::SetRenderTarget(float r, float g, float b)
{
	ID3D11RenderTargetView * pRenderTargetView;
	ID3D11DepthStencilView * pDepthStencilView;
	m_pContext->OMGetRenderTargets( 1, &pRenderTargetView, &pDepthStencilView );

	// Clear the back buffer
	float color[4] = { r, g, b, 1.0f };
	m_pContext->ClearRenderTargetView( pRenderTargetView, color );

	// Clear the z-buffer to 1.0 (max depth)
	m_pContext->ClearDepthStencilView( pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
}

void DX11GraphicsEngine::SetRenderTarget(const RenderTexture * pRenderTexture)
{
	pRenderTexture->SetAsRenderTarget();

	ID3D11RenderTargetView * pRenderTargetView;
	ID3D11DepthStencilView * pDepthStencilView;
	m_pContext->OMGetRenderTargets( 1, &pRenderTargetView, &pDepthStencilView );

	// Clear the back buffer
	//float color[4] = { 1, 1, 1, 1.0f };
	//m_pContext->ClearRenderTargetView( pRenderTargetView, color );

	// Clear the z-buffer to 1.0 (max depth)
	m_pContext->ClearDepthStencilView( pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
}

void DX11GraphicsEngine::ResetRenderTarget(const RenderTexture * pRenderTexture)
{
	if (NULL != pRenderTexture)
	{
		pRenderTexture->RestoreRenderTarget();
	}
	else
	{
		// Present our back buffer to our front buffer
		if ( SUCCEEDED( m_pSwapChain->Present( 0, 0 ) ) )
		{
			int i = 0;
		}
	}
}

HRESULT DX11GraphicsEngine::InitDevice()
{
	HRESULT hr = S_OK;

	m_window.GetResolution(m_width, m_height);

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	DXGI_SWAP_CHAIN_DESC sd;
	{
		ZeroMemory( &sd, sizeof( sd ) );
		sd.BufferCount							= 1;
		sd.BufferDesc.Width						= m_width;
		sd.BufferDesc.Height					= m_height;
		sd.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator		= 60;
		sd.BufferDesc.RefreshRate.Denominator	= 1;
		sd.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow							= m_window.GetHWND();
		sd.SampleDesc.Count						= 1;
		sd.SampleDesc.Quality					= 0;
		sd.Windowed								= TRUE;
	}

	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		D3D_DRIVER_TYPE		driverType = driverTypes[driverTypeIndex];
		D3D_FEATURE_LEVEL	featureLevel = D3D_FEATURE_LEVEL_11_0;

		hr = D3D11CreateDeviceAndSwapChain( NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice, &featureLevel, &m_pContext );
		if( SUCCEEDED( hr ) )
			break;
	}
	if( FAILED( hr ) )
		return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if( FAILED( hr ) )
		return hr;

	hr = m_pDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pRenderTargetView );
	pBackBuffer->Release();
	if( FAILED( hr ) )
		return hr;

	// Set z-buffer parameters

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	{
		ZeroMemory( &descDepth, sizeof(descDepth) );
		descDepth.Width					= m_width;
		descDepth.Height				= m_height;
		descDepth.MipLevels				= 1;
		descDepth.ArraySize				= 1;
		descDepth.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count		= 1;
		descDepth.SampleDesc.Quality	= 0;
		descDepth.Usage					= D3D11_USAGE_DEFAULT;
		descDepth.BindFlags				= D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags		= 0;
		descDepth.MiscFlags				= 0;
	}
		
	hr = m_pDevice->CreateTexture2D( &descDepth, NULL, &m_pDepthStencil );
	if( FAILED( hr ) )
		return hr;

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	{
		ZeroMemory( &descDSV, sizeof(descDSV) );
		descDSV.Format				= descDepth.Format;
		descDSV.ViewDimension		= D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice	= 0;
	}

	hr = m_pDevice->CreateDepthStencilView( m_pDepthStencil, &descDSV, &m_pDepthStencilView );
	if( FAILED( hr ) )
		return hr;

	// Bind the backbuffer and the z-buffer to the Context
	// Turn on the z-buffer
	m_pContext->OMSetRenderTargets( 1, &m_pRenderTargetView, m_pDepthStencilView );
	// Turn off the z-buffer
	//m_pContext->OMSetRenderTargets( 1, &m_pRenderTargetView, NULL );

	// Setup the viewport
	D3D11_VIEWPORT vp;
	{
		vp.Width	= static_cast<FLOAT>( m_width );
		vp.Height	= static_cast<FLOAT>( m_height );
		vp.MinDepth	= 0.0f;
		vp.MaxDepth	= 1.0f;
		vp.TopLeftX	= 0;
		vp.TopLeftY	= 0;
	}

	m_pContext->RSSetViewports( 1, &vp );


	// Setup Rasterizer state
	D3D11_RASTERIZER_DESC  RasterDesc;
	{
		// Set primitive type to draw
		{
			// Draw polygons only (is used usual)
			RasterDesc.FillMode = D3D11_FILL_SOLID;

			// Draw edges only (is used for debug)
			//RasterDesc.FillMode = D3D11_FILL_WIREFRAME;
		}
				
		// Set culling mode
		{
			// Draw only front polygons (CW) == Cull back polygons (CCW)
			// CCW = Conter Clock Wise
			// CW = Clock Wise
			RasterDesc.CullMode = D3D11_CULL_BACK;

			// Draw front and back polygons == Turn off culling
			//RasterDesc.CullMode = D3D11_CULL_NONE;
		}
		
		RasterDesc.FrontCounterClockwise	= false;
		RasterDesc.DepthBias				= 0;
		RasterDesc.SlopeScaledDepthBias		= 0.0f;
		RasterDesc.DepthBiasClamp			= 0.0f;
		RasterDesc.DepthClipEnable			= true;
		RasterDesc.ScissorEnable			= false;
		RasterDesc.MultisampleEnable		= false;
		RasterDesc.AntialiasedLineEnable	= false;
	}
    	
	m_pDevice->CreateRasterizerState( &RasterDesc, &m_pRasterizerState );
	m_pContext->RSSetState( m_pRasterizerState );
	

	Application::Instance().SetContext( new DX11GraphicsEngineContext(m_pDevice, m_pContext, this) );
	
	return S_OK;
}

#endif
