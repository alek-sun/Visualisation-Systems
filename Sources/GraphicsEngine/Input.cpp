#include "Input.h"
#include "GraphicsEngine/Internal/InternalInput.h"
#include <iostream>

bool Input::GetKey(KeyCode keyCode)
{
	return InternalInput::GetKey(keyCode);
}

bool Input::GetKeyDown(KeyCode keyCode)
{
	return InternalInput::GetKeyDown(keyCode);
}

bool Input::GetKeyUp(KeyCode keyCode)
{
	return InternalInput::GetKeyUp(keyCode);
}

Vector3 Input::GetMousePosition()
{
	return InternalInput::GetMousePosition();
}

bool Input::GetMouseButton(int button)
{
	return InternalInput::GetMouseButton(button);
}

bool Input::GetMouseButtonDown(int button)
{
	return InternalInput::GetMouseButtonDown(button);
}

bool Input::GetMouseButtonUp(int button)
{
	return InternalInput::GetMouseButtonUp(button);
}
