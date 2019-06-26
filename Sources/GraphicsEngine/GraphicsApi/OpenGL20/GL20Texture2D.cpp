#include "GL20Texture2D.h"
//#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20TextureSampler.h"


GL20Texture2D::GL20Texture2D(const char * filepath)
{
	FIBITMAP * pBitmap = FreeImage_Load( FreeImage_GetFileType(filepath, 0), filepath);
	FIBITMAP * pImage = FreeImage_ConvertTo32Bits(pBitmap);
	
	FreeImage_FlipVertical(pImage); // OpenGL flips texture upside-down, so we should flip too.
	
	m_width  = FreeImage_GetWidth(pImage);
	m_height = FreeImage_GetHeight(pImage);
	
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	{
		void * pPixels = (void*)FreeImage_GetBits(pImage);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pPixels);
		glGenerateMipmapEXT(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FreeImage_Unload(pImage);

	m_pTextureSampler = new GL20TextureSampler( TEXTURE_FILTER_MODE_POINT, TEXTURE_WRAP_MODE_REPEAT );
}

GL20Texture2D::~GL20Texture2D()
{
	glDeleteBuffers(1, &m_texture);
}

void GL20Texture2D::PassToShader(int textureRegister, bool toPixelShader) const
{
	glActiveTexture ( GL_TEXTURE0 + textureRegister );
	glBindTexture   ( GL_TEXTURE_2D, m_texture );

	m_pTextureSampler->PassParamsToShader( textureRegister, toPixelShader );
}
