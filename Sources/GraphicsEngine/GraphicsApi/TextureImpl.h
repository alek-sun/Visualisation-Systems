#pragma once
#include "GraphicsEngine/GraphicsApi/TextureSamplerImpl.h"


// Read about
// http://www.gamedev.net/topic/665663-a-question-on-texture-sampling/
// http://www.learnopengles.com/tag/texel-graphics/
// http://www.clarissewiki.com/common/filtering.html
// https://en.wikipedia.org/wiki/Texture_filtering
// http://www.cdrinfo.com/Sections/Articles/Sources/Introduction_to_3D_graphics/Images/picture_4_large.jpg


/**
* @brief TextureImpl class is the interface for textures (2d-textures, render textures).
* It controls: filter mode, wrap mode, mip maps, anisotropy level.
*/
class TextureImpl
{
public:
	/**
	* @brief Constructs the object.
	*/
	TextureImpl();

	/**
	* @brief Release resources.
	*/
	virtual ~TextureImpl();

	/**
	* @brief Set texture filter mode (Point, Bilinear, Trilinear, Anisotropic).
	* @param [in] filterMode Texture filter mode.
	*/
	void SetFilterMode(TextureFilterMode filterMode);

	/**
	* @brief Set texture wrap mode (Clamp, Repeat)
	* @param [in] wrapMode Texture wrap mode.
	*/
	void SetWrapMode(TextureWrapMode wrapMode);

protected:

	/**
	* @brief Texture sampler.
	* It controls: filter mode, wrap mode, mip maps, anisotropy level.
	*/
	TextureSamplerImpl * m_pTextureSampler;
};
