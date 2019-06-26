#pragma once


// Read about
// http://www.gamedev.net/topic/665663-a-question-on-texture-sampling/
// http://www.learnopengles.com/tag/texel-graphics/
// http://www.clarissewiki.com/common/filtering.html
// https://en.wikipedia.org/wiki/Texture_filtering
// http://www.cdrinfo.com/Sections/Articles/Sources/Introduction_to_3D_graphics/Images/picture_4_large.jpg


/**
* @brief Texture filter mode (Point, Bilinear, Trilinear, Anisotropic).
*/
enum TextureFilterMode
{
	TEXTURE_FILTER_MODE_POINT,		// texture pixels become blocky up close
	TEXTURE_FILTER_MODE_BILINEAR,	// texture samples are averaged
	TEXTURE_FILTER_MODE_TRILINEAR,	// texture samples are averaged and also blended between mipmap levels
	TEXTURE_FILTER_MODE_ANISOTROPIC,// Anisotropic filtering makes textures look better when viewed at a shallow angle,
};
