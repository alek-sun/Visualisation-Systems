#include "GraphicsDevice.h"
#include "GraphicsEngine/GraphicsEngineFabric.h"


GraphicsDeviceImpl * GraphicsDevice::pImpl = NULL;


GraphicsDevice::~GraphicsDevice()
{
	if (NULL != pImpl)
	{
		delete pImpl;
	}
}

void GraphicsDevice::Init()
{
	pImpl = GraphicsEngineFabric::CreateDevice();
}

void GraphicsDevice::SetFillMode( FillMode fillMode )
{
	pImpl->SetFillMode( fillMode );
}

void GraphicsDevice::SetZWrite( bool enable )
{
	pImpl->SetZWrite( enable );
}
