#include "WinInput.h"
#include "GraphicsEngine/Internal/InternalInput.h"
#include <Windowsx.h>

#ifdef CAN_USE_DIRECT_X


void WinInput::Init()
{
	// TODO : Task08
}

void WinInput::Clear()
{
	InternalInput::Clear();
}

void WinInput::Dispatch(MSG & msg)
{
	// If a key event
	if (msg.message >= WM_KEYFIRST && msg.message <= WM_KEYLAST)
	{
		// https://msdn.microsoft.com/en-us/library/windows/desktop/gg153546(v=vs.85).aspx

		UINT winEvent = msg.message;
		
		// A key in Windows OS
		WPARAM winKey = msg.wParam;

		// If a key is pressed down
		if (winEvent == WM_KEYDOWN)
		{
			// Process keys: Shift, Control, Alt
			if (winKey >= VK_SHIFT && winKey <= VK_MENU)
			{
				// TODO : Task08
				// Call InternalInput
			}
			// Process other keys
			else
			{
				// TODO : Task08
				// Call InternalInput
			}
		}

		// If a key is pressed up
		if (winEvent == WM_KEYUP)
		{
			// TODO : Task08
			// Call InternalInput
		}
	}

	// If a mouse event
	if (msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST)
	{
		// TODO : Task08
		// Call InternalInput
	}
}

#endif
