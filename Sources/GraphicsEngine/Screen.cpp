#include "Screen.h"


int Screen::m_width = 0;
int Screen::m_height = 0;


int Screen::GetWidth()
{
	return m_width;
}

int Screen::GetHeight()
{
	return m_height;
}

void Screen::SetResolution(int width, int height)
{
	m_width = width;
	m_height = height;
}
