#pragma once
#include "GraphicsEngine/GraphicsApi/GraphicsDeviceImpl.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"
#include "GraphicsEngine/GraphicsApi/GUIImpl.h"
#include "GraphicsEngine/GraphicsApi/FixedFunctionPipelineImpl.h"
#include "GraphicsEngine/GraphicsApi/MaterialImpl.h"
#include "GraphicsEngine/GraphicsApi/MeshImpl.h"
#include "GraphicsEngine/GraphicsApi/VertexShaderImpl.h"
#include "GraphicsEngine/GraphicsApi/PixelShaderImpl.h"
#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"
#include "GraphicsEngine/GraphicsApi/Texture2DImpl.h"


// Interface to create objects listed below.
// This class is Abstract factory, derived classes implement this interface.
// Separates objects usage from objects creation (a concrete implementation in DX9, DX11, GL20).
// E.g. separates an interface MeshImpl from concrete implementations: DX9Mesh, DX11Mesh.
// Design Patterns: Abstract Factory (role - Abstract Factory).
class GraphicsEngineFabricImpl
{
public:
	virtual GraphicsDeviceImpl *	CreateDevice() = 0;

	virtual GraphicsEngineImpl *	CreateEngine() = 0;

	virtual GUIImpl *				CreateGUI() = 0;

	virtual MeshImpl *				CreateMesh() = 0;
	
	virtual Texture2DImpl *			CreateTexture2D(const char * filepath) = 0;

	virtual RenderTextureImpl *		CreateRenderTexture(int size) = 0;

	virtual MaterialImpl *			CreateMaterial(const char * vertexShaderFilePath, const char * fragmentShaderFilePath) = 0;

	virtual VertexShaderImpl *		CreateVertexShader(const char * filepath) = 0;
	virtual VertexShaderImpl *		CreateVertexShader(const unsigned long * pFunction) = 0;
	
	virtual PixelShaderImpl *		CreatePixelShader(const char * filepath) = 0;
	virtual PixelShaderImpl *		CreatePixelShader(const unsigned long * pFunction) = 0;

	virtual FixedFunctionPipelineImpl * CreateFixedFunctionPipeline() = 0;
};
