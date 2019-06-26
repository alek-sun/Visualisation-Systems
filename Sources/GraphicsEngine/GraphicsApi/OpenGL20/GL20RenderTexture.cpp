#include "GL20RenderTexture.h"
//#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20TextureSampler.h"


GL20RenderTexture::GL20RenderTexture(int width, int height)
	:	m_width(width),
		m_height(height)
{
	// http://learnopengl.com/#!Advanced-Lighting/Shadows/Shadow-Mapping
	// http://fabiensanglard.net/shadowmapping/index.php
	// http://fabiensanglard.net/shadowmappingPCF/index.php

	// TODO
}

GL20RenderTexture::~GL20RenderTexture()
{
	// TODO
}

void GL20RenderTexture::SetAsRenderTarget()
{
	// TODO
}

void GL20RenderTexture::RestoreRenderTarget()
{
	// TODO
}

void GL20RenderTexture::SetTexture(int textureRegister) const
{
	// TODO
}
