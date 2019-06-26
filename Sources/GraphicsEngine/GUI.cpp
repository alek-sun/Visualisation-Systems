#include "GUI.h"
#include "GraphicsEngine/Internal/InternalGUI.h"


void GUI::Label(int x, int y, int w, int h, const std::string & text)
{
	InternalGUI::Label(x, y, w, h, text);
}

void GUI::Label(int x, int y, int w, int h, double number)
{
	InternalGUI::Label(x, y, w, h, number);
}
