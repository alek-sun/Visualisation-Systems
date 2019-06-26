#include "Object.h"
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Meshes/Mesh.h"
#include "GraphicsEngine/Transform.h"


Object::Object(const char * name)
	:	m_pTransform( NULL ),
		m_pMesh		( NULL ),
		m_pMaterial	( NULL ),
		m_isActive	( true )
{
	m_name = (NULL == name) ? "Object" : name;
}

Object::~Object()
{
	// Очищаем список компонент
	{
		std::list<Component *>::iterator iter;
		for (iter = m_components.begin(); iter != m_components.end(); iter++)
		{
			Component * pComponent = (*iter);
			if (NULL != pComponent)
			{
				delete pComponent;
			}
		}

		m_components.clear();
	}

	if (NULL != m_pMaterial)
	{
		m_pMaterial->Deinit();
		delete m_pMaterial;
		m_pMaterial = NULL;
	}

	if (NULL != m_pMesh)
	{
		m_pMesh->Deinit();
		delete m_pMesh;
		m_pMesh = NULL;
	}

	if (NULL != m_pTransform)
	{
		delete m_pTransform;
		m_pTransform = NULL;
	}	
}

void Object::Init()
{
	if (NULL != m_pMesh)
	{
		m_pMesh->Init();
	}

	if (NULL != m_pMaterial)
	{
		m_pMaterial->Init();
	}
}

void Object::AddComponent(Component * pComponent)
{
	m_components.push_back(pComponent);
	pComponent->Init(this);
}

bool Object::IsActive() const
{
	return m_isActive;
}

void Object::SetActive(bool isActive)
{
	m_isActive = isActive;
}

void Object::Update() const
{
	std::list<Component *>::const_iterator iter;
	for (iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		Component * pComponent = (*iter);
		if (NULL != pComponent)
		{
			pComponent->Update();
		}
	}
}
