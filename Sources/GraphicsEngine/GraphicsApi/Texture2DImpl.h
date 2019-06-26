#pragma once
#include "GraphicsEngine/GraphicsApi/TextureImpl.h"


/**
* @brief Texture2DImpl class is the interface for 2d-textures.
*/
class Texture2DImpl : public TextureImpl
{
public:
	/**
	* @brief Pass texture to the pixel shader.
	* @param [in] textureRegister Position number in whole list of textures for the pixel shader.
	* @param [in] toPixelShader If is called from pixel shader then true, from vertex shader - false.
	*/
	virtual void PassToShader(int textureRegister, bool toPixelShader) const = 0;
};
