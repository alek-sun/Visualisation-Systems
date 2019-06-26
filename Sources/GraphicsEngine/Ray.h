#pragma once
#include "GraphicsEngine/Vector3.h"


/**
* @brief Struct for the ray (contains origin and direction).
*/
struct Ray
{
	Ray(const Vector3 & origin, const Vector3 & direction)
	{
		this->origin = origin;
		this->direction = direction;
	}

	/**
	* @brief The origin of the ray (point where the ray starts).
	*/
	Vector3 origin;

	/**
	* @brief The direction of the ray.
	*/
	Vector3 direction;
};
