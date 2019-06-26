#include "DX9GUI.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"
#include "GraphicsEngine/Application.h"

bool				DX9GUI::isInited	= false;
LPDIRECT3DDEVICE9	DX9GUI::m_pDevice	= NULL;
ID3DXFont *			DX9GUI::m_pFont		= NULL;

void DX9GUI::Init()
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;
}

HRESULT DX9GUI::InitFont(UINT iheight, UINT iwidth, UINT iweight)
{
	// http://www.firststeps.ru/mfc/directx/dr3d/r.php?22
	// http://forum.shelek.ru/index.php/topic,19278.0.html
	// http://www.cyberforum.ru/directx/thread888719.html
	// http://www.gamedev.ru/code/forum/?id=91973
	
	// TODO: Task03

	return S_OK;
};

void DX9GUI::Label(int x, int y, int w, int h, const char * pText)
{
	if (!isInited)
	{
		Init();
	}

	InitFont(25, 10, 100);

	RECT rect;
	{
		ZeroMemory(&rect,sizeof(RECT));
		rect.left	= x;
		rect.top	= y;
		rect.bottom	= x + w;
		rect.right	= y + h;
	}
	
	m_pFont->DrawTextA(NULL, pText, (int)strlen(pText), &rect, DT_LEFT | DT_NOCLIP, 0xffffffff);
}

#endif
