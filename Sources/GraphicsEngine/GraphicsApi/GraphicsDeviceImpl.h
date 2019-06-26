#pragma once


enum FillMode
{
	FILL_MODE_SOLID = 0,
	FILL_MODE_WIREFRAME
};


/**
* @brief GraphicsDeviceImpl class is an interface for the graphics device.
* Every graphics device is associated with a specific window (renders a scene to this window).
*/
class GraphicsDeviceImpl
{
public:
	virtual ~GraphicsDeviceImpl() { }

	/**
	* @brief Set fill mode (solid or wireframe).
	* @param [in] fillMode The fill mode (solid or wireframe).
	*/
	virtual void SetFillMode( FillMode fillMode ) = 0;

	/**
	* @brief Enable/disable writing to the z-buffer (depth buffer).
	* @param [in] enable Enable/disable writing.
	*/
	virtual void SetZWrite( bool enable ) = 0;
};
