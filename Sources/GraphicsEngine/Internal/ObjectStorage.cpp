#include "ObjectStorage.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Materials/Material.h"


std::map<int, std::vector<Object *>> ObjectStorage::m_renderMap;


void ObjectStorage::Push( Object * pObject )
{
	if (NULL == pObject) return;
	
	Material * pMaterial = pObject->m_pMaterial;
	if (NULL == pMaterial) return;

	int renderQueue = pMaterial->GetRenderQueue();

	// if group of objects with a key equals to the renderQueue doesn't exist
	if ( m_renderMap.find( renderQueue ) == m_renderMap.end() )
	{
		m_renderMap[renderQueue] = std::vector<Object *>();
	}
	
	// push the object pointer to appropriate group of objects
	m_renderMap[renderQueue].push_back( pObject );
}

void ObjectStorage::TraverseAllObjects( void (*foo)(const Object * pObject, Material * pSpecialMaterial), Material * pSpecialMaterial )
{
	std::map<int, std::vector<Object *>>::iterator iter;
	
	// for each group
	for (iter = m_renderMap.begin(); iter != m_renderMap.end(); ++iter)
	{
		std::vector<Object *> & group = iter->second;

		// for each object in the group
		for (size_t i = 0; i < group.size(); ++i)
		{
			Object * pObject = group[i];

			foo( pObject, pSpecialMaterial );
		}
	}
}
