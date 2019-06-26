#include "DX11GraphicsDevice.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsDevice.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsEngineContext.h"
#include "GraphicsEngine/Application.h"


DX11GraphicsDevice::DX11GraphicsDevice()
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX11GraphicsEngineContext * pDX11Context = static_cast<const DX11GraphicsEngineContext *>( pContext );
	m_pDevice = pDX11Context->m_pDevice;
	m_pContext = pDX11Context->m_pContext;

	CreateRasteriserState();
	CreateStencilState();
}

DX11GraphicsDevice::~DX11GraphicsDevice()
{
	SAFE_RELEASE( m_pDSS_ZWriteOff );
	SAFE_RELEASE( m_pDSS_ZWriteOn );
	SAFE_RELEASE( m_pRasterizerStateWireframe );
	SAFE_RELEASE( m_pRasterizerStateSolid );	
}

void DX11GraphicsDevice::SetFillMode( FillMode fillMode )
{
	if (fillMode == FILL_MODE_SOLID)
	{
		// Draw polygons only (is used usual)
		m_pContext->RSSetState( m_pRasterizerStateSolid );
	}
	else if (fillMode == FILL_MODE_WIREFRAME)
	{
		// Draw edges only (is used for debug)
		m_pContext->RSSetState( m_pRasterizerStateWireframe );
	}
}

void DX11GraphicsDevice::SetZWrite( bool enable )
{
	// https://msdn.microsoft.com/ru-ru/library/windows/desktop/bb205074(v=vs.85).aspx

	if (enable)
	{
		m_pContext->OMSetDepthStencilState( m_pDSS_ZWriteOn, 1 );
	}
	else
	{
		m_pContext->OMSetDepthStencilState( m_pDSS_ZWriteOff, 1 );
	}
}


void DX11GraphicsDevice::CreateRasteriserState()
{
	// Setup Rasterizer state
	D3D11_RASTERIZER_DESC  desc;
	{			
		// Set culling mode
		{
			// Draw only front polygons (CW) == Cull back polygons (CCW)
			// CCW = Conter Clock Wise
			// CW = Clock Wise
			desc.CullMode = D3D11_CULL_BACK;

			// Draw front and back polygons == Turn off culling
			//desc.CullMode = D3D11_CULL_NONE;
		}
		
		desc.FrontCounterClockwise	= false;
		desc.DepthBias				= 0;
		desc.SlopeScaledDepthBias	= 0.0f;
		desc.DepthBiasClamp			= 0.0f;
		desc.DepthClipEnable		= true;
		desc.ScissorEnable			= false;
		desc.MultisampleEnable		= false;
		desc.AntialiasedLineEnable	= false;
	}
    
	// Draw polygons only (is used usual)
	desc.FillMode = D3D11_FILL_SOLID;
	m_pDevice->CreateRasterizerState( &desc, &m_pRasterizerStateSolid );

	// Draw edges only (is used for debug)
	desc.FillMode = D3D11_FILL_WIREFRAME;
	m_pDevice->CreateRasterizerState( &desc, &m_pRasterizerStateWireframe );
}

void DX11GraphicsDevice::CreateStencilState()
{
	// https://msdn.microsoft.com/ru-ru/library/windows/desktop/bb205074(v=vs.85).aspx

	// Setup depth stencil state
	D3D11_DEPTH_STENCIL_DESC desc;
	{
		// Depth test parameters
		desc.DepthEnable	= true;
		desc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthFunc		= D3D11_COMPARISON_LESS;

		// Stencil test parameters
		desc.StencilEnable		= true;
		desc.StencilReadMask	= 0xFF;
		desc.StencilWriteMask	= 0xFF;

		// Stencil operations if pixel is front-facing
		desc.FrontFace.StencilFailOp		= D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilDepthFailOp	= D3D11_STENCIL_OP_INCR;
		desc.FrontFace.StencilPassOp		= D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;

		// Stencil operations if pixel is back-facing
		desc.BackFace.StencilFailOp			= D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilDepthFailOp	= D3D11_STENCIL_OP_DECR;
		desc.BackFace.StencilPassOp			= D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;
	}

	// Enable writing to the z-buffer (depth buffer).
	desc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
	desc.DepthFunc		= D3D11_COMPARISON_LESS;
	m_pDevice->CreateDepthStencilState( &desc, &m_pDSS_ZWriteOn );

	// Disable writing to the z-buffer (depth buffer).
	desc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ZERO;
	desc.DepthFunc		= D3D11_COMPARISON_ALWAYS;
	m_pDevice->CreateDepthStencilState( &desc, &m_pDSS_ZWriteOff );
}

#endif
