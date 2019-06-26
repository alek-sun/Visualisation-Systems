#pragma once
#include "GraphicsEngine/TextureFilterMode.h"
#include "GraphicsEngine/TextureWrapMode.h"


/**
* @brief GL20TextureSampler class is the interface for the texture sampler.
* It controls: filter mode, wrap mode, mip maps, anisotropy level.
*/
class TextureSamplerImpl
{
public:
	/**
	* @brief Release resources.
	*/
	virtual ~TextureSamplerImpl() { };

	/**
	* @brief Set texture filter mode (Point, Bilinear, Trilinear, Anisotropic).
	* @param [in] filterMode Texture filter mode.
	*/
	virtual void SetFilterMode(TextureFilterMode filterMode) = 0;

	/**
	* @brief Set texture wrap mode (Clamp, Repeat).
	* @param [in] wrapMode Texture wrap mode.
	*/
	virtual void SetWrapMode(TextureWrapMode wrapMode) = 0;
	
	/**
	* @brief Pass texture to the pixel shader.
	* Pass parameters: filter mode, wrap mode, mip maps, anisotropy level.
	* @param [in] textureRegister Position number in whole list of textures for the shader.
	* @param [in] toPixelShader If is called from pixel shader then true, from vertex shader - false.
	*/
	virtual void PassParamsToShader(int textureRegister, bool toPixelShader) const = 0;
};
