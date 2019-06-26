#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include <Windows.h>


class WinInput
{
public:
	static void Init();
	static void Clear();
	static void Dispatch(MSG & msg);

private:
};

#endif
