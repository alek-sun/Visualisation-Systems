#pragma once
#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"


class GraphicsEngineContext
{
public:
	GraphicsEngineContext(GraphicsEngineImpl * pImpl)
		: m_pImpl(pImpl)
	{
	
	}

	GraphicsEngineImpl * m_pImpl;
};
