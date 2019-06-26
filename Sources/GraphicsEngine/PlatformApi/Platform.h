#pragma once

#ifdef _WIN32
	#define PLATFORM_WINDOWS
#elif __linux__
    #define PLATFORM_LINUX
#else
#endif


#ifdef PLATFORM_WINDOWS
	//#define CAN_USE_DIRECT_X
	#define CAN_USE_OPEN_GL
#else
	#ifdef PLATFORM_LINUX
	#define CAN_USE_OPEN_GL	
	#endif
#endif