#pragma once
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/GraphicsApi/TextureSamplerImpl.h"


/**
* @brief GL20TextureSampler class is the implementation for the texture sampler.
* It controls: filter mode, wrap mode, mip maps, anisotropy level.
*/
class GL20TextureSampler : public TextureSamplerImpl
{
public:
	/**
	* @brief Constructs the object.
	* @param [in] filterMode Texture filter mode (Point, Bilinear, Trilinear, Anisotropic).
	* @param [in] wrapMode Texture wrap mode (Clamp, Repeat).
	*/
	GL20TextureSampler(TextureFilterMode filterMode, TextureWrapMode wrapMode);
	
	/**
	* @brief Release resources.
	*/
	virtual ~GL20TextureSampler();

	/**
	* @brief Set texture filter mode (Point, Bilinear, Trilinear, Anisotropic).
	* @param [in] filterMode Texture filter mode.
	*/
	void SetFilterMode(TextureFilterMode filterMode);

	/**
	* @brief Set texture wrap mode (Clamp, Repeat).
	* @param [in] wrapMode Texture wrap mode.
	*/
	void SetWrapMode(TextureWrapMode wrapMode);
	
	/**
	* @brief Pass texture to the pixel shader.
	* Pass parameters: filter mode, wrap mode, mip maps, anisotropy level.
	* @param [in] textureRegister Position number in whole list of textures for the shader.
	* @param [in] toPixelShader If is called from pixel shader then true, from vertex shader - false.
	*/
	void PassParamsToShader(int textureRegister, bool toPixelShader) const;

private:

	/**
	* @brief Minification filter - a single pixel on the screen can correspond to a large collection of texels.
	* Each texel is smaller than a pixel, usually means that object is far away from the camera.	
	*/
	GLint	m_minFilterMode;

	/**
	* @brief Magnification filter - a single pixel on the screen can correspond to anything from a tiny portion of a texel.
	* Each texel is bigger than a pixel, usually means that object is pretty close to the camera.	
	*/
	GLint	m_magFilterMode;

	/**
	* @brief Texturewrap mode (Clamp, Repeat).
	*/
	GLint	m_wrapMode;

	GLint m_filterMode;
	
	/**
	* @brief Anisotropic filtering is enabled/disabled.
	*/
	bool	m_useAniso;

	bool	m_useMipMaps;
};
