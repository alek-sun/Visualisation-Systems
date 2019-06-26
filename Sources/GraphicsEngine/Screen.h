#pragma once


class Screen
{
public:

	// Screen resolution - width  in pixels
	static int GetWidth();

	// Screen resolution - heigth in pixels
	static int GetHeight();
	
	static void SetResolution(int width, int height);	

private:
	static int m_width;
	static int m_height;
};
