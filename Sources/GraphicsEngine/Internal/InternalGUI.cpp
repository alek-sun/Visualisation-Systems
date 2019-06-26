#include "InternalGUI.h"
#include "GraphicsEngine/GraphicsEngineFabric.h"


std::vector<GUIElement>	InternalGUI::elements;
GUIImpl *				InternalGUI::pImpl = NULL;


void InternalGUI::Label(int x, int y, int w, int h, const std::string & text)
{
	GUIElement elem;
	{
		elem.x = x;
		elem.y = y;
		elem.w = w;
		elem.h = h;
		elem.text = text;
	}

	elements.push_back(elem);
}

void InternalGUI::Label(int x, int y, int w, int h, double number)
{
	const std::string & text = std::to_string( static_cast<long double>(number) );
	Label(x, y, w, h, text);
}

void InternalGUI::Update()
{
	if (NULL == pImpl)
	{
		pImpl = GraphicsEngineFabric::CreateGUI();
	}

	for (size_t i = 0; i < elements.size(); ++i)
	{
		const GUIElement & elem = elements[i];
		pImpl->Label(elem.x, elem.y, elem.w, elem.h, elem.text.c_str());
	}

	elements.clear();
}
