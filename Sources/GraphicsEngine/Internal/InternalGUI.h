#pragma once
#include "GraphicsEngine/GraphicsApi/GUIImpl.h"
#include "GraphicsEngine/GUIElement.h"
#include <vector>


/**
* @brief GUI class is the realization for user graphic interface (GUI), e.g. display a text on the screen.
* It's an internal class - the graphics engine uses this class, a user couldn't use this class.
*/
class InternalGUI
{
public:

	/**
	* @brief Draw a label with text on the screen.
	* @param [in] x,y Coordinates of left-top label corner.
	* @param [in] w,h Width and height of the label.
	* @param [in] text Text to be displayed.
	*/
	static void Label(int x, int y, int w, int h, const std::string & text);

	/**
	* @brief Draw a label with double number on the screen
	* @param [in] x,y Coordinates of left-top label corner.
	* @param [in] w,h Width and height of the label.
	* @param [in] number Number to be displayed.
	*/
	static void Label(int x, int y, int w, int h, double number);

	/**
	* @brief Is called every frame by graphics engine.
	*/
	static void Update();

private:
	// Forbid construction and destruction of objects
	InternalGUI();
	~InternalGUI();
	InternalGUI(const InternalGUI &);
	InternalGUI& operator= (InternalGUI const&);

	// a list of gui-elements to draw at the current frame
    static std::vector<GUIElement> elements;

	// a graphics api implementation (on DirectX 9 / DirectX 11 / OpenGL 2.0)
	static GUIImpl * pImpl;
};
