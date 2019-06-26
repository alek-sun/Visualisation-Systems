#pragma once
#include "GraphicsEngine/GraphicsApi/GraphicsEngineFabricImpl.h"


// Class implements an interface GraphicsEngineFabricImpl in DirectX9.
// Class creates objects listed below if DirectX9 is chosen as Graphics API
// Design Patterns: Abstract Factory (role - Concrete Factory).
class GL20GraphicsEngineFabric : public GraphicsEngineFabricImpl
{
public:
	GraphicsDeviceImpl *	CreateDevice();

	GraphicsEngineImpl *	CreateEngine();

	GUIImpl *				CreateGUI();

	MeshImpl *				CreateMesh();
	
	Texture2DImpl *			CreateTexture2D(const char * filepath);

	RenderTextureImpl *		CreateRenderTexture(int size);

	MaterialImpl *			CreateMaterial(const char * vertexShaderFilePath, const char * fragmentShaderFilePath);
	
	VertexShaderImpl *		CreateVertexShader(const char * filepath);
	VertexShaderImpl *		CreateVertexShader(const unsigned long * pFunction);
	
	PixelShaderImpl *		CreatePixelShader(const char * filepath);
	PixelShaderImpl *		CreatePixelShader(const unsigned long * pFunction);
	
	FixedFunctionPipelineImpl * CreateFixedFunctionPipeline();
};
