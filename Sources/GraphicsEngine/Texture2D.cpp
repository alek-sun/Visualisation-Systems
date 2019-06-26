#include "Texture2D.h"
#include "GraphicsEngine/GraphicsEngineFabric.h"
#include "GraphicsEngine/Application.h"
#include <cstddef>


Texture2D::Texture2D(const char * filepath)
{
	std::string dataDirectory = Application::Instance().GetDataDirectory();
	std::string fullpath = dataDirectory + std::string( filepath );

	pImpl = GraphicsEngineFabric::CreateTexture2D( fullpath.c_str() );
}

Texture2D::~Texture2D()
{
	delete pImpl;
	pImpl = NULL;
}

void Texture2D::SetFilterMode(TextureFilterMode filterMode)
{
	pImpl->SetFilterMode( filterMode );
}

void Texture2D::SetWrapMode(TextureWrapMode wrapMode)
{
	pImpl->SetWrapMode( wrapMode );
}

const Texture2DImpl * Texture2D::GetImplPointer() const
{
	return pImpl;
}

void Texture2D::PassToShader(int textureRegister, bool toPixelShader) const
{
	pImpl->PassToShader( textureRegister, toPixelShader );
}
