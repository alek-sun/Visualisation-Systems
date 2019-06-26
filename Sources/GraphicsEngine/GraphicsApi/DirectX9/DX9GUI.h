#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "DX9.h"
#include "GraphicsEngine/GraphicsApi/GUIImpl.h"

// http://www.firststeps.ru/mfc/directx/dr3d/r.php?22
// http://forum.shelek.ru/index.php/topic,19278.0.html
// http://www.cyberforum.ru/directx/thread888719.html
// http://www.gamedev.ru/code/forum/?id=91973


class DX9GUI : public GUIImpl
{
public:
	void Label(int x, int y, int w, int h, const char * pText);	

private:
	static void Init();
	static HRESULT InitFont(UINT iheight, UINT iwidth, UINT iweight);

	static bool isInited;

	static LPDIRECT3DDEVICE9	m_pDevice;
	static LPD3DXFONT			m_pFont;
};

#endif
