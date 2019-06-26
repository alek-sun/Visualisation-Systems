#pragma once
#include <string>


/**
* @brief GUI class is the interface for user graphic interface (GUI), e.g. display a text on the screen.
*/
class GUI
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

private:
	// Forbid construction and destruction of objects
	GUI();
	~GUI();
	GUI(const GUI &);
	GUI& operator= (GUI const&);
};
