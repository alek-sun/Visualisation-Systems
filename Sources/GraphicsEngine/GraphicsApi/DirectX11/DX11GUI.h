#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "DX11.h"
#include "GraphicsEngine/GraphicsApi/GUIImpl.h"


class DX11GUI : public GUIImpl
{
public:
	void Label(int x, int y, int w, int h, const char * pText);	
};

#endif
