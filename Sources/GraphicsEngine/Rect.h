#pragma once


struct Rect
{
	Rect(float x = 0.0f, float y = 0.0f, float w = 1.0f, float h = 1.0f)
		: x(x), y(y), w(w), h(h)
	{

	}

	float x, y, w, h;
};
