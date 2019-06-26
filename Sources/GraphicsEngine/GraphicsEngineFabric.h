#pragma once
#include "GraphicsEngine/GraphicsApi/GraphicsEngineFabricImpl.h"


// Class provides interface to create objects listed below.
// Separates objects usage from objects creation (a concrete implementation in DX9, DX11, GL20).
// E.g. separates an interface MeshImpl from concrete implementations: DX9Mesh, DX11Mesh.
// Design Patterns: Abstract Factory, Facade.
class GraphicsEngineFabric
{
public:
	static GraphicsDeviceImpl *	CreateDevice();

	static GraphicsEngineImpl *	CreateEngine();

	static GUIImpl *			CreateGUI();

	static MeshImpl *			CreateMesh();
	
	static Texture2DImpl *		CreateTexture2D(const char * filepath);

	static RenderTextureImpl *	CreateRenderTexture(int size);

	static MaterialImpl *		CreateMaterial(const char * vertexShaderFilePath, const char * fragmentShaderFilePath);

	static VertexShaderImpl *	CreateVertexShader(const char * filepath);
	static VertexShaderImpl *	CreateVertexShader(const unsigned long * pFunction);
	
	static PixelShaderImpl *	CreatePixelShader(const char * filepath);
	static PixelShaderImpl *	CreatePixelShader(const unsigned long * pFunction);

	static FixedFunctionPipelineImpl * CreateFixedFunctionPipeline();

private:
	static GraphicsEngineFabricImpl * pImpl;
};
