#pragma once
#include "Scene.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineContext.h"
#include <string>


// TODO: Посмотреть шаблон Singleton<class T>, возможно его нужно использовать
// чтобы не писать методы и поля Singleton-а в каждом таком классе.
class Application
{
public:	
	static Application & Instance();

	GraphicsEngineContext *	GetContext();
	void					SetContext(GraphicsEngineContext * pContext);

	Scene & GetScene();
	
    const std::string & GetShadersDirectory();
	const std::string & GetDataDirectory();

	int		argc;
	char **	argv;
	
private:
	Application();	
	Application(const Application &);
	~Application();
	
	Scene m_scene;

	// TODO: Убрать это поле из класса (чтобы все классы не были завязаны на GraphicsEngine)
	GraphicsEngineContext * m_pContext;

	std::string	m_shadersDirectory;
	std::string	m_dataDirectory;
};
