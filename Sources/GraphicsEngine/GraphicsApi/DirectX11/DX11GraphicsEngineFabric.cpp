#include "DX11GraphicsEngineFabric.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsDevice.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsEngine.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GUI.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11Material.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11Mesh.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11VertexShader.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11PixelShader.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11RenderTexture.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11Texture2D.h"
//#include "GraphicsEngine/GraphicsApi/DirectX9/FixedFunctionPipelineDX9.h"


GraphicsDeviceImpl * DX11GraphicsEngineFabric::CreateDevice()
{
	return new DX11GraphicsDevice();
}

GraphicsEngineImpl * DX11GraphicsEngineFabric::CreateEngine()
{
	return new DX11GraphicsEngine();
}

GUIImpl * DX11GraphicsEngineFabric::CreateGUI()
{
	return new DX11GUI();
}

MeshImpl * DX11GraphicsEngineFabric::CreateMesh()
{
	return new DX11Mesh();
}

Texture2DImpl * DX11GraphicsEngineFabric::CreateTexture2D(const char * filepath)
{
	return new DX11Texture2D(filepath);
}

RenderTextureImpl * DX11GraphicsEngineFabric::CreateRenderTexture(int size)
{
	return new DX11RenderTexture(size);
}

MaterialImpl * DX11GraphicsEngineFabric::CreateMaterial(const char * vertexShaderFilePath, const char * fragmentShaderFilePath)
{
	return new DX11Material(vertexShaderFilePath, fragmentShaderFilePath);
}

VertexShaderImpl * DX11GraphicsEngineFabric::CreateVertexShader(const char * filepath)
{
	return new DX11VertexShader(filepath);
}

VertexShaderImpl * DX11GraphicsEngineFabric::CreateVertexShader(const unsigned long * pFunction)
{
	return new DX11VertexShader(pFunction);
}

PixelShaderImpl * DX11GraphicsEngineFabric::CreatePixelShader(const char * filepath)
{
	return new DX11PixelShader(filepath);
}

PixelShaderImpl * DX11GraphicsEngineFabric::CreatePixelShader(const unsigned long * pFunction)
{
	return new DX11PixelShader(pFunction);
}

FixedFunctionPipelineImpl * DX11GraphicsEngineFabric::CreateFixedFunctionPipeline()
{
	//return new FixedFunctionPipelineDX9();
	return NULL;
}

#endif
