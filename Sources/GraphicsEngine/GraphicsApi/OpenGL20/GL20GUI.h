#pragma once
#include "GL20.h"
#include "GraphicsEngine/GraphicsApi/GUIImpl.h"


class GL20GUI : public GUIImpl
{
public:
	void Label(int x, int y, int w, int h, const char * pText);
};
