#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "DX9.h"
#include "GraphicsEngine/GraphicsApi/GraphicsDeviceImpl.h"


/**
* @brief GraphicsDeviceImpl class is an implementation of the graphics device.
* Every graphics device is associated with a specific window (renders a scene to this window).
*/
class DX9GraphicsDevice : public GraphicsDeviceImpl
{
public:
	DX9GraphicsDevice();

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
	LPDIRECT3DDEVICE9	m_pDevice;
};

#endif
