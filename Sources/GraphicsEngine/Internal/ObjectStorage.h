#pragma once
#include <map>
#include <vector>


class Object;
class Material;


/**
* @brief ObjectStorage class is used to store all objects an traverse them.
* Traverse is used in scene rendering or collision detection.
*/
class ObjectStorage
{
public:

	/**
	* @brief Push the object pointer to the storage.
	* @param [in] pObject The object pointer.
	*/
	static void Push( Object * pObject );

	static void TraverseAllObjects( void (*foo)(const Object * pObject, Material * pSpecialMaterial), Material * pSpecialMaterial );

private:
	ObjectStorage();
	ObjectStorage( ObjectStorage const & );

	/**
	* @brief Render map stores groups of objects (grouped by render queue).
	* std::map<renderQueue, std::vector<Object *>>
	*/
	static std::map<int, std::vector<Object *>> m_renderMap;
};
