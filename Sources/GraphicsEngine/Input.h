#pragma once
#include "GraphicsEngine/KeyCode.h"
#include "GraphicsEngine/Vector3.h"


/**
* @brief Input class is the interface for the user input, e.g. keyboard and mouse.
*/
class Input
{
public:
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
	Input();
	~Input();
	Input(const Input &);
	Input& operator= (Input const&);

	static bool m_keys[];
};
