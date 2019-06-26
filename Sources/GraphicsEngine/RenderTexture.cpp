#include "RenderTexture.h"
#include "GraphicsEngine/GraphicsEngineFabric.h"
#include <cstddef>


RenderTexture::RenderTexture(int size)
	:	m_pImpl(NULL),
		m_size(size)
{
	m_pImpl = GraphicsEngineFabric::CreateRenderTexture(size);
}

RenderTexture::~RenderTexture()
{
	if (NULL != m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = NULL;
	}
}

void RenderTexture::SetAsRenderTarget() const
{
	m_pImpl->SetAsRenderTarget();
}

void RenderTexture::RestoreRenderTarget() const
{
	m_pImpl->RestoreRenderTarget();
}

const RenderTextureImpl * RenderTexture::GetImplPointer() const
{
	return m_pImpl;
}

int RenderTexture::GetWidth() const
{
	return m_size;
}

int RenderTexture::GetHeight() const
{
	return m_size;
}
