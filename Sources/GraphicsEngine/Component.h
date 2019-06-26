#pragma once
#include <stdlib.h>

class Object;


/**
* @brief Base class for scripts attached to the Object.
*/
class Component
{
public:
	Component() 
	{
		m_pObject = NULL;
	}

	virtual ~Component() {}

	/**
	* @brief Initializes the object.
	* Used to allocate custom resources.
	*/
	virtual void Init(Object * pObject)
	{
		m_pObject = pObject;
	}
	
	/**
	* @brief Returns pointer to the Object.
	* Used to access to the Object's Transform, Material, Mesh, ...
	*/
	Object * GetObjectPtr() const
	{
		return m_pObject;
	}

	/**
	* @brief Is called at each frame.
	* Used to execute custom code at each frame.
	*/
	virtual void Update() { }

protected:

	/**
	* @brief The pointer to the object.
	*/
	Object * m_pObject;
};
