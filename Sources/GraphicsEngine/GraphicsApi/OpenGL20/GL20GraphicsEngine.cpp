#include "GL20GraphicsEngine.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Internal/InternalGUI.h"
#include "GraphicsEngine/Screen.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20Input.h"


GL20GraphicsEngine * pGL20Engine = NULL;

void GL20Render()
{
	if (NULL != pGL20Engine)
	{
		pGL20Engine->Render1();
	}
}

void GL20Reshape(int w, int h)
{
	if (NULL != pGL20Engine)
	{
		pGL20Engine->Reshape(w, h);
	}
}

void GL20LetterKeyDownFunc(unsigned char key, int x, int y)
{
	GL20Input::SetLetterKeyDown(key);
}

void GL20LetterKeyUpFunc(unsigned char key, int x, int y)
{
	GL20Input::SetLetterKeyUp(key);
}

void GL20SpecialKeyDownFunc(int key, int x, int y)
{
	GL20Input::SetSpecialKeyDown(key);
}

void GL20SpecialKeyUpFunc(int key, int x, int y)
{
	GL20Input::SetSpecialKeyUp(key);
}

void GL20MouseButtonsFunc(int button, int state, int x, int y)
{
	GL20Input::SetMouseButtonsEvent(button, state, x, y);
	GL20Input::SetMouseMotionEvent(x, y);
}

void GL20MouseMotionFunc(int x, int y)
{
	GL20Input::SetMouseMotionEvent(x, y);
}

GL20GraphicsEngine::GL20GraphicsEngine()
	:	m_scene(Application::Instance().GetScene()),
		m_pWindowTitle("Graphics Engine (OpenGL 2.0)")
{

}

void GL20GraphicsEngine::Init()
{
	pGL20Engine = this;

	Screen::SetResolution(512, 512);
		
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ms683156(v=vs.85).aspx
	// https://msdn.microsoft.com/en-us/library/windows/desktop/bb776391(v=vs.85).aspx
	//LPSTR cmdLine = GetCommandLineA();
	// C language
	//#include <stdlib.h>
	//wcstombs(
	//mbstowcs(
	
	// C++ language
	//std::wstring wc( cSize, L'#' );
	//mbstowcs( &wc[0], c, cSize );

	int		argc = Application::Instance().argc;
	char **	argv = Application::Instance().argv;
	glutInit(&argc, argv); // Initialize GLUT
	
	// Set up basic display buffers (backbuffer and z-buffer)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	// Create the application's window
	m_window = -1;
	{
		glutInitWindowPosition(100, 100);			// Set the position of the window
		glutInitWindowSize(Screen::GetWidth(), Screen::GetHeight());			// Set the width and height of the window
		m_window = glutCreateWindow(m_pWindowTitle);	// Set the title for the window
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	}

	GLenum err = glewInit(); 
	if (GLEW_OK != err) 
	{ 
		return;
	}
	
	glutDisplayFunc(GL20Render); // Tell GLUT to use the method "display" for rendering  
	glutReshapeFunc(GL20Reshape);
	
	glutKeyboardFunc	(GL20LetterKeyDownFunc);
	glutKeyboardUpFunc	(GL20LetterKeyUpFunc);
	glutSpecialFunc		(GL20SpecialKeyDownFunc);	
	glutSpecialUpFunc	(GL20SpecialKeyUpFunc);
	
	glutMouseFunc(GL20MouseButtonsFunc);
	glutPassiveMotionFunc(GL20MouseMotionFunc);
	glutMotionFunc(GL20MouseMotionFunc);
	
	glFrontFace(GL_CW);

	// Set primitive type to draw
	{
		// Draw polygons only (is used usual)
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

		// Draw edges only (is used for debug)
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}

	// Set culling mode
	{
		// Draw only front polygons (CW) == Cull back polygons (CCW)
		// CCW = Conter Clock Wise
		// CW = Clock Wise
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	
		// Draw front and back polygons == Turn off culling
		//glDisable(GL_CULL_FACE);
	}

	// Turn on the z-buffer
	glEnable( GL_DEPTH_TEST );
	glDepthMask( GL_TRUE );
	glDepthFunc( GL_LESS );

	GraphicsEngineContext * pContext = new GraphicsEngineContext(this);
	Application::Instance().SetContext( pContext );

	GL20Input::Init();

	m_scene.Init();
}

void GL20GraphicsEngine::Deinit()
{
	m_scene.Deinit();
	
	// TODO: Поймать событие закрытия окна и освободить ресурсы
	pGL20Engine = NULL;
}

void GL20GraphicsEngine::Render()
{
	GL20Input::Clear();

	// Dispatch window events
	glutMainLoopEvent();
	
	// Render scene - Tell OpenGL to call GL20Render()
	if (IsRunning())
	{
		glutPostRedisplay();		
	}
}

bool GL20GraphicsEngine::IsRunning()
{
	return (glutGetWindow() == m_window);
}

void GL20GraphicsEngine::SetViewport(Rect rect, int width, int height)
{
	// http://docs.gl/gl2/glViewport
	
	m_viewportRect = rect;
	// Invert y-axis
	m_viewportRect.y = 1.0f - m_viewportRect.y - m_viewportRect.h;

	GLint	x = static_cast<GLint>	( m_viewportRect.x * width);
	GLint	y = static_cast<GLint>	( m_viewportRect.y * height);
	GLsizei	w = static_cast<GLsizei>( m_viewportRect.w * width);
	GLsizei	h = static_cast<GLsizei>( m_viewportRect.h * height);

	glViewport(x, y, w, h);
}

void GL20GraphicsEngine::SetResolution(int width, int height)
{
	Screen::SetResolution(width, height);
	SetViewport(m_viewportRect, width, height);
}

void GL20GraphicsEngine::SetRenderTarget(float r, float g, float b)
{
	// Choose buffers to be cleared (color buffer and z-buffer)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Clear the color buffer to blue
	glClearColor(r, g, b, 1.0f);
	
	// Clear the z-buffer
	glClearDepth(1.0f);
}

void GL20GraphicsEngine::SetRenderTarget(const RenderTexture * pRenderTexture)
{
	pRenderTexture->SetAsRenderTarget();
}

void GL20GraphicsEngine::ResetRenderTarget(const RenderTexture * pRenderTexture)
{
	if (NULL != pRenderTexture)
	{
		pRenderTexture->RestoreRenderTarget();
	}
}

void GL20GraphicsEngine::Render1()
{
	{
		m_scene.Update();
		m_scene.Render();

		InternalGUI::Update();
	}

	// Flush the OpenGL buffers to the window
	//glFlush();
	glutSwapBuffers();
}

// Reshapes the window appropriately
void GL20GraphicsEngine::Reshape(int w, int h)
{
	SetResolution(w, h);
}
