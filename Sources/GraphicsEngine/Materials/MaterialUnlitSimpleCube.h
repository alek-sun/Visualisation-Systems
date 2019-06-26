#pragma once
#include "GraphicsEngine/Materials/Material.h"


/**
* @brief Unlit material class doesn't take into account light sources.
* It's for rendering the object without lightning (even light sources exist in a scene).
* For more details, see class Material
*/
class MaterialUnlitSimpleCube : public Material
{
public:
	/**
	* @brief Constructs the object.
	*/
	MaterialUnlitSimpleCube();

	/**
	* @brief Initialize the material and necessary data here.
	*/
	virtual void Init();

	/**
	* @brief Deinitialize the material and necessary data here.
	*/
	virtual void Deinit();
	
	/**
	* @brief Pass all necessary for rendering data to vertex and pixel shaders (is called before rendering).
	* @param [in] pObject Pointer to an object that is being rendered now.
	*/
	virtual void SetMaterial(const Object * pObject);
};
