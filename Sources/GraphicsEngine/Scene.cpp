// TODO: ”казать полный путь дл¤ #include во всЄм проекте
#include "GraphicsEngine/Scene.h"

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Meshes/Mesh.h"
#include "GraphicsEngine/Object.h"

#include "GraphicsEngine/Internal/ObjectStorage.h"


void Scene::Init()
{
	m_pCamera = NULL;

	m_pSelectedObject = NULL;
}

void Scene::Deinit()
{
	// ”дал¤ем объекты
	{
		//std::list<const Object *>::iterator iter;
		//for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
		for (size_t i = 0; i < m_objects.size(); ++i)
		{
			//const Object * pObject = (*iter);
			const Object * pObject = m_objects[i];
			delete pObject;
		}
	}

	m_lights.clear();
	m_objects.clear();	

	// ”дал¤ем камеру
	m_pCamera = NULL;
}

void Scene::AddObject(Object * pObject)
{
	if (NULL == pObject)
	{
		return;
	}

	pObject->Init();
	m_objects.push_back( pObject );
	ObjectStorage::Push( pObject );
}

void Scene::AddLight(Light * pLight)
{
	if (NULL == pLight)
	{
		return;
	}

	m_lights.push_back(pLight);

	if (NULL != pLight->GetObjectPtr())
	{
		AddObject(pLight->GetObjectPtr());
	}
}

void Scene::SetSelectedObject(Object * pObject)
{
	m_pSelectedObject = pObject;
}

Object * Scene::GetSelectedObject()
{
	return m_pSelectedObject;
}

void Scene::SetCamera(Camera * pCamera)
{
	if (NULL != pCamera)
	{
		m_pCamera = pCamera;
		//m_objects.push_back(m_pCamera->GetObjectPtr());
	}
}

//Camera & Scene::GetCamera() const
//{
//	return (*m_pCamera);
//}

Camera * Scene::GetCamera()
{
	return m_pCamera;
}

const std::list<const Light *> & Scene::GetLights() const
{
	return m_lights;
}

const std::vector<const Object *> & Scene::GetObjects() const
{
	return m_objects;
}

void Scene::Update()
{
	m_pCamera->GetObjectPtr()->Update();

	//std::list<const Object *>::iterator iter;
	//for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	for (size_t i = 0; i < m_objects.size(); ++i)
	{
		//const Object * pObject = (*iter);
		const Object * pObject = m_objects[i];
		if (NULL != pObject)
		{
			pObject->Update();
		}
	}
}

void Scene::Render()
{
	if (NULL == m_pCamera)
	{
		return;
	}

	m_pCamera->Render();
}
