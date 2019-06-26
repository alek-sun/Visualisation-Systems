#pragma once
#include "GraphicsEngine/GraphicsApi/TextureImpl.h"
#include <stddef.h>


TextureImpl::TextureImpl()
	:	m_pTextureSampler(NULL) 
{

}

TextureImpl::~TextureImpl()
{
	if (NULL != m_pTextureSampler)
	{
		delete m_pTextureSampler;
		m_pTextureSampler = NULL;
	}
}

void TextureImpl::SetFilterMode(TextureFilterMode filterMode)
{
	if (NULL != m_pTextureSampler)
	{
		m_pTextureSampler->SetFilterMode( filterMode );
	}
}

void TextureImpl::SetWrapMode(TextureWrapMode wrapMode)
{
	if (NULL != m_pTextureSampler)
	{
		m_pTextureSampler->SetWrapMode( wrapMode );
	}
}
