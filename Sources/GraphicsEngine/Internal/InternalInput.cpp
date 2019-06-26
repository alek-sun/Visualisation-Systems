#include "InternalInput.h"
#include "GraphicsEngine/GraphicsEngineFabric.h"
#include <iostream>

bool	InternalInput::m_keys[512];
bool	InternalInput::m_keysDown[512];
bool	InternalInput::m_keysUp[512];

Vector3	InternalInput::m_mousePosition;
bool	InternalInput::m_mouseButtons[3];
bool	InternalInput::m_mouseButtonsDown[3];
bool	InternalInput::m_mouseButtonsUp[3];


InternalInput::InternalInput()
{
	for (int i = 0; i < 512; ++i)
	{
		m_keys[i] = false;
		m_keysDown[i] = false;
		m_keysUp[i] = false;
	}

	for (int i = 0; i < 3; ++i)
	{
		m_mouseButtons[i]		= false;
		m_mouseButtonsDown[i]	= false;
		m_mouseButtonsUp[i]		= false;
	}
}

void InternalInput::Clear()
{
	//std::memset(m_mouseButtonsDown, false, sizeof(m_mouseButtonsDown));
	//std::memset(m_mouseButtonsUp, false, sizeof(m_mouseButtonsUp));

	for (int i = 0; i < 512; ++i)
	{
		m_keysDown[i] = false;
		m_keysUp[i] = false;
	}

	for (int i = 0; i < 3; ++i)
	{
		m_mouseButtonsDown[i]	= false;
		m_mouseButtonsUp[i]		= false;
	}
}

void InternalInput::SetKeyDown(unsigned int key)
{
	if (!m_keys[key])
	{
		m_keysDown[key] = true;
	}

	m_keys[key] = true;	
	std::cout << key << std::endl;
}

void InternalInput::SetKeyUp(unsigned int key)
{
	if (m_keys[key])
	{
		m_keysUp[key] = true;
	}

	m_keys[key] = false;
	//std::cout << key << std::endl;
}

void InternalInput::SetMousePosition(int x, int y)
{
	m_mousePosition.x = x;
	m_mousePosition.y = y;
	m_mousePosition.z = 0;
}

void InternalInput::SetMouseButton(int button, bool pressed)
{
	if (button < 0 || button >= 3) return;

	if (pressed)
	{
		m_mouseButtons[button]		= true;
		m_mouseButtonsDown[button]	= true;
	}
	else
	{
		m_mouseButtons[button]		= false;
		m_mouseButtonsUp[button]	= true;
	}
}


bool InternalInput::GetKey(KeyCode keyCode)
{
	return m_keys[keyCode];
}

bool InternalInput::GetKeyDown(KeyCode keyCode)
{
	return m_keysDown[keyCode];
}

bool InternalInput::GetKeyUp(KeyCode keyCode)
{
	return m_keysUp[keyCode];
}

Vector3 InternalInput::GetMousePosition()
{
	return m_mousePosition;
}

bool InternalInput::GetMouseButton(int button)
{
	if (button < 0 || button >= 3) return false;

	return m_mouseButtons[button];
}

bool InternalInput::GetMouseButtonDown(int button)
{
	if (button < 0 || button >= 3) return false;

	return m_mouseButtonsDown[button];
}

bool InternalInput::GetMouseButtonUp(int button)
{
	if (button < 0 || button >= 3) return false;

	return m_mouseButtonsUp[button];
}
