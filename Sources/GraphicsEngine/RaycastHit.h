#pragma once
#include "GraphicsEngine/Vector3.h"

class Transform;
class Object;


/**
* @brief Struct for the information about the collision.
*/
struct RaycastHit
{
	/**
	* @brief The object of the collision.
	*/
	Object *	pObject;

	/**
	* @brief The object's transform.
	*/
	Transform *	pTransform;

	/**
	* @brief The point of the collision.
	*/
	Vector3		point;

	/**
	* @brief The distance to the point of the collision.
	*/
	double		distance;
};
