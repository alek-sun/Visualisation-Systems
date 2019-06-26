#include "GL20TextureSampler.h"
//#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsEngineContext.h"
#include "GraphicsEngine/Application.h"

GL20TextureSampler::GL20TextureSampler(TextureFilterMode filterMode, TextureWrapMode wrapMode)
{
	m_useAniso = false;
	m_useMipMaps = false;
	SetFilterMode(filterMode);
	SetWrapMode(wrapMode);
}

GL20TextureSampler::~GL20TextureSampler()
{	
}

void GL20TextureSampler::SetFilterMode(TextureFilterMode filterMode)
{
	// http://www.learnopengles.com/android-lesson-six-an-introduction-to-texture-filtering/
	// https://www.opengl.org/wiki/Sampler_Object
	// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/

	if (filterMode == TEXTURE_FILTER_MODE_POINT)	{
		m_useMipMaps = true;
		m_filterMode = GL_NEAREST;
	}
	else if (filterMode == TEXTURE_FILTER_MODE_BILINEAR)	{
		m_useMipMaps = true;
		m_filterMode = GL_LINEAR_MIPMAP_NEAREST;
	}
	else if (filterMode == TEXTURE_FILTER_MODE_TRILINEAR)	{
		m_useMipMaps = true;
		m_filterMode = GL_LINEAR_MIPMAP_LINEAR;
	}
	else if (filterMode == TEXTURE_FILTER_MODE_ANISOTROPIC)	{
		m_useAniso = true;
		m_filterMode = GL_LINEAR_MIPMAP_LINEAR;
	}
}

void GL20TextureSampler::SetWrapMode(TextureWrapMode wrapMode){
	// http://gamedev.stackexchange.com/questions/62548/what-does-changing-gl-texture-wrap-s-t-do

	m_wrapMode = wrapMode;

	if (m_wrapMode == TEXTURE_WRAP_MODE_CLAMP)
	{
		m_wrapMode = GL_CLAMP;
	}
	else if (m_wrapMode == TEXTURE_WRAP_MODE_REPEAT)
	{
		m_wrapMode = GL_REPEAT;
	}
}

void GL20TextureSampler::PassParamsToShader(int textureRegister, bool toPixelShader) const {
	// Set wrap mode (Clamp, Repeat) 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);
	// Set filter mode (Point, Bilinear, Trilinear, Anisotropic)	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMode);
	if (m_useMipMaps) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// Set degree of anisotropic filtering (aniso level)
	if (m_useAniso)	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 10);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);
	}
}
