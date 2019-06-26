#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "DX11.h"
#include "GraphicsEngine/GraphicsApi/GraphicsDeviceImpl.h"


/**
* @brief GraphicsDeviceImpl class is an implementation of the graphics device.
* Every graphics device is associated with a specific window (renders a scene to this window).
*/
class DX11GraphicsDevice : public GraphicsDeviceImpl
{
public:
	DX11GraphicsDevice();
	~DX11GraphicsDevice();

	/**
	* @brief Set fill mode (solid or wireframe).
	* @param [in] fillMode The fill mode (solid or wireframe).
	*/
	void SetFillMode( FillMode fillMode );

	/**
	* @brief Enable/disable writing to the z-buffer (depth buffer).
	* @param [in] enable Enable/disable writing.
	*/
	void SetZWrite( bool enable );

private:
	void CreateRasteriserState();
	void CreateStencilState();

	ID3D11Device *			m_pDevice;
	ID3D11DeviceContext *	m_pContext;

	ID3D11RasterizerState *	m_pRasterizerStateSolid;
	ID3D11RasterizerState *	m_pRasterizerStateWireframe;

	ID3D11DepthStencilState * m_pDSS_ZWriteOn;
	ID3D11DepthStencilState * m_pDSS_ZWriteOff;
};

#endif
