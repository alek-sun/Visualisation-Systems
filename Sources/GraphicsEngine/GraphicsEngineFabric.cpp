#include "GraphicsEngineFabric.h"
#include "GraphicsEngine/PlatformApi/Platform.h"

#ifdef PLATFORM_WINDOWS
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineFabric.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsEngineFabric.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsEngineFabric.h"

//GraphicsEngineFabricImpl * GraphicsEngineFabric::pImpl = new DX9GraphicsEngineFabric();
//GraphicsEngineFabricImpl * GraphicsEngineFabric::pImpl = new DX11GraphicsEngineFabric();
GraphicsEngineFabricImpl * GraphicsEngineFabric::pImpl = new GL20GraphicsEngineFabric();
#endif

#ifdef PLATFORM_LINUX
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsEngineFabric.h"
	
GraphicsEngineFabricImpl * GraphicsEngineFabric::pImpl = new GL20GraphicsEngineFabric();
#endif


GraphicsDeviceImpl * GraphicsEngineFabric::CreateDevice()
{
	return pImpl->CreateDevice();
}

GraphicsEngineImpl * GraphicsEngineFabric::CreateEngine()
{
	return pImpl->CreateEngine();
}

GUIImpl * GraphicsEngineFabric::CreateGUI()
{
	return pImpl->CreateGUI();
}

MeshImpl * GraphicsEngineFabric::CreateMesh()
{
	return pImpl->CreateMesh();
}

Texture2DImpl * GraphicsEngineFabric::CreateTexture2D(const char * filepath)
{
	return pImpl->CreateTexture2D(filepath);
}

RenderTextureImpl *	GraphicsEngineFabric::CreateRenderTexture(int size)
{
	return pImpl->CreateRenderTexture(size);
}

MaterialImpl * GraphicsEngineFabric::CreateMaterial(const char * vertexShaderFilePath, const char * fragmentShaderFilePath)
{
	return pImpl->CreateMaterial(vertexShaderFilePath, fragmentShaderFilePath);
}

VertexShaderImpl * GraphicsEngineFabric::CreateVertexShader(const char * filepath)
{
	return pImpl->CreateVertexShader(filepath);
}

VertexShaderImpl * GraphicsEngineFabric::CreateVertexShader(const unsigned long * pFunction)
{
	return pImpl->CreateVertexShader(pFunction);
}

PixelShaderImpl * GraphicsEngineFabric::CreatePixelShader(const char * filepath)
{
	return pImpl->CreatePixelShader(filepath);
}

PixelShaderImpl * GraphicsEngineFabric::CreatePixelShader(const unsigned long * pFunction)
{
	return pImpl->CreatePixelShader(pFunction);
}

FixedFunctionPipelineImpl * GraphicsEngineFabric::CreateFixedFunctionPipeline()
{
	return pImpl->CreateFixedFunctionPipeline();
}
