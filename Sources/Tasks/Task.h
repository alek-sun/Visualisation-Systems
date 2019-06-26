#pragma once


/**
* @brief Basic class for create custom scene.
*/
class Task
{
public:
	/**
	* @brief Constructs the object.
	*/
	virtual ~Task() { }

	/**
	* @brief Initializes the object.
	* Used to allocate custom resources.
	*/
	virtual void Init()		{ }
	
	/**
	* @brief Is called at each frame.
	* Used to execute custom code at each frame.
	*/
	virtual void Update()	{ }
};
