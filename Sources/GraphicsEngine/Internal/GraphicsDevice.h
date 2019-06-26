#pragma once
#include "GraphicsEngine/GraphicsApi/GraphicsDeviceImpl.h"


/**
* @brief GraphicsDevice class is used to set parameters at the video card.
* Every graphics device is associated with a specific window (renders a scene to this window).
*/
class GraphicsDevice
{
public:
	~GraphicsDevice();

	static void Init();

	/**
	* @brief Set fill mode (solid or wireframe).
	* @param [in] fillMode The fill mode (solid or wireframe).
	*/
	static void SetFillMode( FillMode fillMode );

	/**
	* @brief Enable/disable writing to the z-buffer (depth buffer).
	* @param [in] enable Enable/disable writing.
	*/
	static void SetZWrite( bool enable );

private:	
	static GraphicsDeviceImpl * pImpl;
};
