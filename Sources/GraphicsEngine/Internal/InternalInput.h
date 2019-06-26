#pragma once
#include "GraphicsEngine/KeyCode.h"
#include "GraphicsEngine/Vector3.h"


/**
* @brief Input class is the implementation for the user input, e.g. keyboard and mouse.
* It's an internal class - the graphics engine uses this class, a user couldn't use this class.
*/
class InternalInput
{
public:
	/**
	* @brief Clear keyboard and mouse events.
	* Is called every frame by graphics engine.
	*/
	static void Clear();

	/**
	* @brief Pass the code of pressed key.
	* @param [in] keyCode Key code.
	* Is called by graphics engine.
	*/
	static void SetKeyDown(unsigned int key);

	/**
	* @brief Pass the code of released key.
	* @param [in] keyCode Key code.
	* Is called by graphics engine.
	*/
	static void SetKeyUp(unsigned int key);

	// Sets the current mouse position in pixel coordinates
	/**
	* @brief Sets the current mouse position in pixel coordinates.
	* @param [in] x,y Pixel coordinates.
	* Is called by graphics engine.
	* 
	*/
	static void SetMousePosition(int x, int y);
	
	/**
	* @brief Sets the current mouse button event.
	* @param [in] button Mouse button to check (0 - left, 1 - right, 2 - middle).
	* @param [in] pressed Is true if mouse button was pressed, false - otherwise.
	* Is called by graphics engine.
	*/
	static void SetMouseButton(int button, bool pressed);

	/**
	* @brief Return true if user is holding the key.
	* @param [in] keyCode Key code to check.
	*/
	static bool GetKey(KeyCode keyCode);

	/**
	* @brief Returns true during the frame the user starts pressing down the key.
	* @param [in] keyCode Key code to check.
	*/
	static bool GetKeyDown(KeyCode keyCode);

	/**
	* @brief Returns true during the frame the user releases the key.
	* @param [in] keyCode Key code to check.
	*/
	static bool GetKeyUp(KeyCode keyCode);

	/**
	* @brief Return current mouse position in pixel coordinates.
	*/
	static Vector3 GetMousePosition();

	/**
	* @brief Return true if mouse button is held down.
	* @param [in] button Mouse button to check (0 - left, 1 - right, 2 - middle).
	*/
	static bool GetMouseButton(int button);

	/**
	* @brief Return true if mouse button was pressed down at the current frame.
	* @param [in] button Mouse button to check (0 - left, 1 - right, 2 - middle).
	*/
	static bool GetMouseButtonDown(int button);
	
	/**
	* @brief Return true if mouse button was released at the current frame.
	* @param [in] button Mouse button to check (0 - left, 1 - right, 2 - middle).
	*/
	static bool GetMouseButtonUp(int button);

private:
	// Forbid construction and destruction of objects
	InternalInput();
	~InternalInput();
	InternalInput(const InternalInput &);
	InternalInput& operator= (InternalInput const&);

	static bool m_keys[];
	static bool m_keysDown[];
	static bool m_keysUp[];

	// The current mouse position in pixel coordinates
	static Vector3 m_mousePosition;
	static bool m_mouseButtons[];
	static bool m_mouseButtonsDown[];
	static bool m_mouseButtonsUp[];
};
