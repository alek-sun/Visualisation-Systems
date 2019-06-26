#include "DX9GraphicsDevice.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"
#include "GraphicsEngine/Application.h"


DX9GraphicsDevice::DX9GraphicsDevice()
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;
}

void DX9GraphicsDevice::SetFillMode( FillMode fillMode )
{
	if (fillMode == FILL_MODE_SOLID)
	{
		// Draw polygons only (is used usual)
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	else if (fillMode == FILL_MODE_WIREFRAME)
	{
		// Draw edges only (is used for debug)
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
}

void DX9GraphicsDevice::SetZWrite( bool enable )
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/bb172599(v=vs.85).aspx

	if (enable)
	{
		m_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
		m_pDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	}
	else
	{
		m_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
		m_pDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );
	}
}

#endif
