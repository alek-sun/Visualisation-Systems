#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_OPEN_GL


class GL20Input
{
public:
	static void Init();

	static void Clear();
	
	static void SetLetterKeyDown	(unsigned char key);
	static void SetLetterKeyUp		(unsigned char key);
	static void SetSpecialKeyDown	(unsigned char key);
	static void SetSpecialKeyUp		(unsigned char key);

	static void SetMouseButtonsEvent(int button, int state, int x, int y);
	static void SetMouseMotionEvent(int x, int y);

private:
};

#endif
