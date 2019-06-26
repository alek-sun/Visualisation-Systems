#pragma once


// Read about
// http://www.gamedev.net/topic/665663-a-question-on-texture-sampling/
// http://www.learnopengles.com/tag/texel-graphics/
// http://www.clarissewiki.com/common/filtering.html
// https://en.wikipedia.org/wiki/Texture_filtering
// http://www.cdrinfo.com/Sections/Articles/Sources/Introduction_to_3D_graphics/Images/picture_4_large.jpg


/**
* @brief Texture wrap mode (Clamp, Repeat).
*/
enum TextureWrapMode
{
	TEXTURE_WRAP_MODE_CLAMP,  // tile the texture one time
	TEXTURE_WRAP_MODE_REPEAT, // tile the texture multiple times
};
