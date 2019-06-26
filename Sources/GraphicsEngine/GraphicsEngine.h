#pragma once
#include "GraphicsEngine/GraphicsApi/GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"


class GraphicsEngine
{
public:
	static GraphicsEngine & Instance();

	void Init();
	void Deinit();

	void Render();
	bool IsRunning();
	
private:
	// TODO: Сделать по всему проекту префикс m_ (почитать С++ code style)
	GraphicsEngineImpl * pGraphicsEngineImpl;

	GraphicsEngine();
	GraphicsEngine( const GraphicsEngine & );
	static GraphicsEngine * pEngine;
};
