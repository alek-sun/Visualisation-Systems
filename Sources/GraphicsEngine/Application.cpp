#include "Application.h"
#include "GraphicsEngine/Directory.h"


Application & Application::Instance()
{
	// TODO: ѕереписать все Singleton подобным образом
	// Ёто нужно, чтобы вызывались деструкторы
	static Application app;
	
	return app;
}

Application::Application()
{
	argv = NULL;
	
	if (Directory::Exists("./Shaders"))
	{
		// Application is run by exe-file
		m_shadersDirectory	= "./Shaders/";
		m_dataDirectory		= "./Data/";
	}
	else
	{
		// Application is run from IDE (i.e. Visual Studio)
		m_shadersDirectory	= "../Sources/GraphicsEngine/Shaders/";
		m_dataDirectory		= "../Data/";
	}
}

Application::~Application()
{
	
}

GraphicsEngineContext * Application::GetContext()
{
	return m_pContext;
}

void Application::SetContext(GraphicsEngineContext * pContext)
{
	m_pContext = pContext;
}

Scene & Application::GetScene()
{
	return m_scene;
}

const std::string & Application::GetShadersDirectory()
{
	return m_shadersDirectory;
}

const std::string & Application::GetDataDirectory()
{
	return m_dataDirectory;
}
